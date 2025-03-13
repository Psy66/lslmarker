# 🚀 LSL Maker Event

![Version](https://img.shields.io/badge/Version-1.0.0-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Python](https://img.shields.io/badge/Python-3.8%2B-yellow)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)

A tool for creating and sending events to an LSL (Lab Streaming Layer) stream. The project is implemented in two versions: **Python** (with a graphical interface) and **C++** (for Windows).

---

## 📦 Project Overview

The LSL Maker Event tool allows researchers to send markers (events) to an LSL stream in real-time. It is useful for synchronizing external events (e.g., button presses) with physiological data streams (e.g., EEG, ECG).

The project includes:
- A **Python version** with a simple graphical interface (GUI) built using `tkinter`.
- A **C++ version** for Windows, built using Visual Studio and the LSL library.

---

## 📂 Repository Structure

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
├── release/             # Pre-built releases
│   └── LSL_Maker_Event_ver1.0.zip # Windows x64 version
├── LICENSE              # MIT License
└── README.md            # Project description (this file)
```

---

## 🐍 Python Version

### 🌟 Features
- Simple and intuitive graphical interface.
- Supports up to 5 customizable events.
- Easy to extend and modify.

### 🔧 Installation
1. Ensure you have Python 3.8 or higher installed.
2. Install the required dependencies:
   ```bash
   pip install -r python_ver/requirements.txt
   ```

### 🚀 Running the Program
Navigate to the `python_ver` folder and run:
```bash
python gui.py
```

---

## 🖥️ C++ Version

### 🌟 Features
- Lightweight and fast.
- Compatible with Windows.
- Uses the LSL library for real-time marker streaming.

### 🔧 Installation
1. Open the `cpp_ver/lslmaker.sln` file in Visual Studio.
2. Build the solution (Build Solution).
3. Run the compiled `.exe` file.

### 📥 Pre-built Release
If you don't want to build the project yourself, you can download the pre-built Windows x64 version:
- [LSL_Maker_Event_ver1.0.zip](release/LSL_Maker_Event_ver1.0.zip)

### 📚 Dependencies
- [LSL Library](https://github.com/sccn/liblsl): Ensure the LSL library is installed and linked correctly.

---

## 👨‍💻 Author
- **Tim Liner**  
  Email: psy66@narod.ru

---

## 📜 License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments
- Thanks to the [LSL community](https://github.com/sccn/liblsl) for providing the Lab Streaming Layer library.

---

# 🚀 LSL Maker Event (на русском)

Инструмент для создания и отправки событий в поток LSL (Lab Streaming Layer). Проект реализован в двух версиях: **Python** (с графическим интерфейсом) и **C++** (для Windows).

---

## 📦 Описание проекта

Инструмент LSL Maker Event позволяет исследователям отправлять маркеры (события) в поток LSL в реальном времени. Это полезно для синхронизации внешних событий (например, нажатий кнопок) с физиологическими данными (например, EEG, ECG).

Проект включает:
- **Версию на Python** с простым графическим интерфейсом (GUI), созданным с использованием `tkinter`.
- **Версию на C++** для Windows, созданную с использованием Visual Studio и библиотеки LSL.

---

## 📂 Структура репозитория

```
lslmarker/
├── python_ver/          # Версия программы на Python
│   ├── gui.py           # Основной скрипт Python с графическим интерфейсом
│   ├── requirements.txt # Зависимости Python
│   └── ...              # Другие файлы Python
├── cpp_ver/             # Версия программы на C++
│   ├── lslmaker.sln     # Файл решения Visual Studio
│   ├── lslmaker.cpp     # Основной файл на C++
│   └── ...              # Другие файлы C++
├── release/             # Готовые сборки
│   └── LSL_Maker_Event_ver1.0.zip # Версия для Windows x64
├── LICENSE              # Лицензия MIT
└── README.md            # Описание проекта (этот файл)
```

---

## 🐍 Версия на Python

### 🌟 Возможности
- Простой и интуитивно понятный графический интерфейс.
- Поддержка до 5 настраиваемых событий.
- Легко расширяется и модифицируется.

### 🔧 Установка
1. Убедитесь, что у вас установлен Python 3.8 или выше.
2. Установите необходимые зависимости:
   ```bash
   pip install -r python_ver/requirements.txt
   ```

### 🚀 Запуск программы
Перейдите в папку `python_ver` и выполните:
```bash
python gui.py
```

---

## 🖥️ Версия на C++

### 🌟 Возможности
- Легковесная и быстрая.
- Совместима с Windows.
- Использует библиотеку LSL для потоковой передачи маркеров в реальном времени.

### 🔧 Установка
1. Откройте файл `cpp_ver/lslmaker.sln` в Visual Studio.
2. Соберите решение (Build Solution).
3. Запустите скомпилированный `.exe` файл.

### 📥 Готовая сборка
Если вы не хотите собирать проект самостоятельно, вы можете скачать готовую версию для Windows x64:
- [LSL_Maker_Event_ver1.0.zip](release/LSL_Maker_Event_ver1.0.zip)

### 📚 Зависимости
- [Библиотека LSL](https://github.com/sccn/liblsl): Убедитесь, что библиотека LSL установлена и правильно подключена.

---

## 👨‍💻 Автор
- **Tim Liner**  
  Email: psy66@narod.ru

---

## 📜 Лицензия
Этот проект распространяется под лицензией MIT. Подробности см. в файле [LICENSE](LICENSE).

---

## 🙏 Благодарности
- Спасибо сообществу [LSL](https://github.com/sccn/liblsl) за предоставление библиотеки Lab Streaming Layer.
```
