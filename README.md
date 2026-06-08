# MP3 Tag Reader & Editor

A lightweight command-line application developed in C for reading and editing MP3 ID3 metadata tags using binary file handling techniques.

---

## Features

* Read MP3 metadata tags
* Edit song title
* Modify artist name
* Update album information
* Change genre and year
* Edit comments field
* Efficient binary file processing
* Command-line interface support

---

## Technologies Used

* C Programming
* File Handling
* Structures
* Command Line Arguments
* Binary File Operations
* Modular Programming

---

## Project Architecture

```text id="5u0d1q"
├── main.c
├── view.c
├── edit.c
├── view.h
├── edit.h
├── common.h
├── Makefile
└── sample.mp3
```

---

## Compilation

```bash id="n05mdv"
gcc *.c -o mp3_editor
```

---

## Execution

### View MP3 Tags

```bash id="7o3gg0"
./mp3_editor -v sample.mp3
```

### Edit MP3 Tags

```bash id="gq9wz0"
./mp3_editor -e -t "New Song Title" sample.mp3
```

---

## Core Concepts Implemented

* MP3 ID3 tag parsing
* Binary file manipulation
* Dynamic memory handling
* Modular software design
* CLI-based interaction

---

## Future Enhancements

* GUI-based interface
* Batch tag editing
* Album artwork extraction
* Unicode metadata support
* Cross-platform compatibility

---

## Learning Outcomes

This project strengthened practical knowledge in:

* Low-level file operations
* Data parsing techniques
* Structured C programming
* Real-world metadata processing

---

## Author

Shareef Sab
Engineering Student | Embedded & Software Enthusiast
