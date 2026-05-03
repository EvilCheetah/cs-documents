# CS-4203 Requirements Document 2.0 (RD 2.0)

This repository contains the LaTeX source code for the Requirements Document 2.0 for a Calendar System.

## Project Overview

This document details the requirements and analysis models for a Calendar System. The proposed system architecture includes:
- **Frontend:** React
- **Backend API:** Python FastAPI Server
- **Database:** PostgreSQL

Key actors identified in the system:
- **Super Admin:** Can add/remove users and manage the system.
- **Mentor:** Can create events, view the calendar, and invite users.
- **Mentee:** Can join/leave events, view event info, and view the calendar.

## Prerequisites

To build this document, you will need:
- A TeX distribution (e.g., TeX Live, MiKTeX, MacTeX) with `latexmk` installed.
- [Task](https://taskfile.dev/) (a task runner/build tool).
- Required LaTeX packages:
  - `tikz` and `standalone` (for compiling graphics)
  - `import` (for modular document structure)
  - Packages listed in `src/config/usepackage.tex`: `amssymb`, `appendix`, `babel`, `booktabs`, `caption`, `datatool`, `datetime2`, `enumitem`, `fancyhdr`, `float`, `fontenc`, `geometry`, `graphicx`, `hyperref`, `inputenc`, `microtype`, `parskip`, `pdfpages`, `subcaption`, `tabularx`, `titlesec`, `xcolor`, `zref-totpages`
- `latexpand` (required for the `task merge` command).

## Building the Document

This project uses `Taskfile.yaml` to manage build tasks.

### Full Build

To compile the graphics and then build the final PDF document:

```bash
task build
```
This will automatically compile the TikZ graphics in `src/content/figures/` and generate `RD 2.0.pdf` in the project root directory.

### Compile Graphics Only

To compile only the TikZ diagrams into standalone PDFs:

```bash
task compile:graphics
```

### Clean Up Temporary Files

To clean up auxiliary files generated during the LaTeX build process:

```bash
task cleanup
```

### Merge LaTeX Files

To merge all included LaTeX files into a single standalone `.tex` file (useful for submission or analysis):

```bash
task merge
```

## Repository Structure

- `Taskfile.yaml`: Build configuration and tasks.
- `src/`: Contains all LaTeX source files.
  - `main.tex`: The entry point for the document.
  - `config/`: Configuration files and package imports.
  - `commands/`: Custom LaTeX commands.
  - `content/`: The main document content organized by sections (Business Requirements, System Features, Analysis Models, etc.) and appendices.
  - `content/figures/`: TikZ source files for the analysis models (Use Case, Architecture, Context-Level Data Flow diagrams).
  - `data/`: CSV data and data import configurations (e.g., team members).
  - `assets/`: Static image assets.
