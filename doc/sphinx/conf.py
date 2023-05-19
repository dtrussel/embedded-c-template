# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

from pathlib import Path

MBED_PROJECT_ROOT = Path(__file__).resolve().parents[2]


# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'mbed lib documentation'
author = 'mbed lib contributors'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.imgmath',
    'sphinx.ext.todo',
    'sphinx_rtd_theme',
    'breathe'
    ]

templates_path = ['_templates']
exclude_patterns = []

# -- breathe configuration ---------------------------------------------------
# https://breathe.readthedocs.io/en/latest/index.html

doxygen_output_dir = MBED_PROJECT_ROOT / "build" / "doxygen" 
breathe_projects = {"mbed": str(doxygen_output_dir / "xml")}
breathe_default_project = "mbed"
breathe_domain_by_extension = {
    "h": "c",
    "c": "c",
}
breathe_show_enumvalue_initializer = True
breathe_default_members = ("members", )

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
    "papersize": "a4paper",
    "maketitle": open(MBED_PROJECT_ROOT / "doc" / "sphinx" / "_static" / "latex" / "title.tex").read(),
    "preamble": open(MBED_PROJECT_ROOT / "doc" / "sphinx" / "_static" / "latex" / "preamble.tex").read(),
    "fontpkg": r"\usepackage{charter}",
    "sphinxsetup": ",".join(
        (
            "verbatimwithframe=false",
            "VerbatimColor={HTML}{f0f2f4}",
            "InnerLinkColor={HTML}{2980b9}",
            "warningBgColor={HTML}{e9a499}",
            "warningborder=0pt",
            r"HeaderFamily=\rmfamily\bfseries",
        )
    ),
}
latex_logo = str(MBED_PROJECT_ROOT / "doc" /"sphinx" / "_static" / "images" / "mbed-logo.pdf")
