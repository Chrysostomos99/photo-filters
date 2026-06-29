# Image Filtering Program (C++)

An object-oriented **C++** application for processing **PPM** images by applying
configurable filters. Built for the *Programming in C++* course.

## Overview

The program reads a PPM image, applies one or more filters to its pixel data, and
writes the result to a new file (prefixed with `filtered_`). It is designed around
a small, reusable class hierarchy rather than ad-hoc image code.

## Design

- **`Image`** — represents the image; built on a generic, templated `Array` of pixels.
- **`Vec3` / `Color`** — generic three-dimensional vector and RGB color types used per pixel.
- **`Filter`** — base type for filters, applied to an image through **operator overloading**
  (e.g. `image = filter << image`).
- Concrete filters:
  - **Gamma** — gamma correction.
  - **Linear** — linear transform of pixel values (a *negative* image is produced as a special case).

Filters are selected and parameterized from the **command line**.

## How to run

Open the Visual Studio solution and build it:

```
filter.sln
```

Then run the produced executable, passing the filter and its parameters as arguments,
for example:

```bash
filter -f gamma <y>
filter -f linear <a> <c>
```

The output image is written next to the input as `filtered_<filename>`.

> The program supports **PPM** images only.

## Project structure

```
filter/
  mainApp.cpp        Command-line entry point and argument parsing
  Image.h / .cpp     Image container
  Filter.h / .cpp    Filter base type
  FilterGamma.*      Gamma filter
  FilterLinear.*     Linear filter
  Vec3.h, Color.h    Pixel math / color types
  Array.h            Generic templated container
  filter.sln         Visual Studio solution
```

## Tech stack

- C++ (object-oriented design, templates, operator overloading)
- Visual Studio
