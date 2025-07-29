#!/usr/bin/env python3

"""
test cases that are only relevant to run in CI
"""

import os
import platform
import subprocess
import sys

import pytest

sys.path.append(os.path.join(os.path.dirname(__file__), "../tests"))
from gvtest import (  # pylint: disable=wrong-import-position
    ROOT,
    build_system,
    dot,
    freedesktop_os_release,
    is_cmake,
    is_macos,
    is_mingw,
    is_static_build,
    run,
    which,
)


@pytest.mark.parametrize(
    "binary",
    [
        "acyclic",
        "bcomps",
        "ccomps",
        "circo",
        "cluster",
        "diffimg",
        "dijkstra",
        "dot",
        "dot2gxl",
        "dot_builtins",
        "edgepaint",
        "fdp",
        "gc",
        "gml2gv",
        "graphml2gv",
        "gv2gml",
        "gv2gxl",
        "gvcolor",
        "gvedit",
        "gvgen",
        "gvmap",
        "gvmap.sh",
        "gvpack",
        "gvpr",
        "gxl2dot",
        "gxl2gv",
        "mingle",
        "mm2gv",
        "neato",
        "nop",
        "osage",
        "patchwork",
        "prune",
        "sccmap",
        "sfdp",
        "smyrna",
        "tred",
        "twopi",
        "unflatten",
        "vimdot",
    ],
)
def test_existence(binary: str):
    """
    check that a given binary was built and is on $PATH
    """

    os_id = freedesktop_os_release().get("ID")

    # https://gitlab.com/graphviz/graphviz/-/issues/1834
    if os_id == "rocky" and binary == "smyrna":
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip("smyrna is not built for Rocky due to lacking libgts")

    if os_id == "rocky" and binary == "mingle":
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip("mingle is not built for Rocky due to lacking libANN")

    if binary == "mingle" and is_cmake() and is_mingw():
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip(f"{binary} is not built on some Windows due to lacking libANN")

    if binary == "gvedit" and platform.system() == "Windows" and not is_mingw():
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip(f"{binary} is not built on Windows due to lacking Qt")

    # Smyrna dependencies are not avaiable in other jobs
    if binary == "smyrna" and platform.system() != "Linux":
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip("smyrna is not built on non-Linux due to lacking dependencies")

    if binary == "gvmap.sh" and platform.system() == "Windows":
        pytest.skip(f"{binary} detection is unreliable on Windows")

    if binary == "vimdot" and platform.system() == "Windows":
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip(f"{binary} is not installed on Windows")

    if binary == "vimdot" and not is_cmake() and is_macos():
        check_that_tool_does_not_exist(binary, os_id)
        pytest.skip("https://gitlab.com/graphviz/graphviz/-/issues/2423")

    if binary == "dot_builtins" and is_static_build():
        pytest.skip("dot_builtins may not be built in a static build")

    assert which(binary) is not None


def check_that_tool_does_not_exist(tool, os_id):
    """
    validate that the given tool does *not* exist
    """
    assert which(tool) is None, (
        f"{tool} has been resurrected in the "
        f"{build_system()} build on {os_id}. Please remove skip."
    )


def test_1786():
    """
    png:gd format should be supported
    https://gitlab.com/graphviz/graphviz/-/issues/1786
    """

    # run a trivial graph through Graphviz
    dot("png:gd", source="digraph { a -> b; }")


def test_2469():
    """
    svgz format should be supported
    https://gitlab.com/graphviz/graphviz/-/issues/2469
    """

    # run a trivial graph through Graphviz
    dot("svgz", source="digraph { a -> b; }")


def test_installation():
    """
    check that Graphviz reports the expected version number
    """

    expected_version = run([sys.executable, ROOT / "gen_version.py"]).strip()

    actual_version_string = run(["dot", "-V"], stderr=subprocess.STDOUT)
    try:
        actual_version = actual_version_string.split()[4]
    except IndexError:
        pytest.fail(f"Malformed version string: {actual_version_string}")
    assert actual_version == expected_version
