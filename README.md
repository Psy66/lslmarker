# LSL Maker Event

A tool for creating and sending events to an LSL (Lab Streaming Layer) stream. The project is implemented in two versions: **Python** (with a graphical interface) and **C++** (for Windows).

---

## Project Overview

The LSL Maker Event tool allows researchers to send markers (events) to an LSL stream in real-time. It is useful for synchronizing external events (e.g., button presses) with physiological data streams (e.g., EEG, ECG).

The project includes:
- A **Python version** with a simple graphical interface (GUI) built using `tkinter`.
- A **C++ version** for Windows, built using Visual Studio and the LSL library.

---

## Repository Structure

```
lslmarker/
├── python_ver/          # Python version of the program
│   ├── gui.py           # Main Python script with the GUI
│   ├── requirements.txt # Python dependencies
│   └── ...              # Other Python files
├── cpp_ver/             # C++ version of the program
│   ├── lslmaker.sln     # Visual Studio solution file
│   ├── lslmaker.cpp     # Main C++ source file
│   └── ...              # Other C++ files
└── README.md            # Project description (this file)
```

---

## Python Version

### Features
- Simple and intuitive graphical interface.
- Supports up to 5 customizable events.
- Easy to extend and modify.

### Installation
1. Ensure you have Python 3.x installed.
2. Install the required dependencies:
   ```bash
   pip install -r python_ver/requirements.txt
   ```

### Running the Program
Navigate to the `python_ver` folder and run:
```bash
python gui.py
```

---

## C++ Version

### Features
- Lightweight and fast.
- Compatible with Windows.
- Uses the LSL library for real-time marker streaming.

### Installation
1. Open the `cpp_ver/lslmaker.sln` file in Visual Studio.
2. Build the solution (Build Solution).
3. Run the compiled `.exe` file.

### Dependencies
- [LSL Library](https://github.com/sccn/liblsl): Ensure the LSL library is installed and linked correctly.

---

## Author
- **Tim Liner**  
  Email: psy66@narod.ru

---

## Acknowledgments
- Thanks to the [LSL community](https://github.com/sccn/liblsl) for providing the Lab Streaming Layer library.
```
