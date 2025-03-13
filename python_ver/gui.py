import tkinter as tk
from pylsl import StreamInfo, StreamOutlet

class LSLMakerEventApp:
	"""
	Класс для создания графического интерфейса LSL Maker Event.
	Позволяет вводить названия событий и отправлять их в LSL-поток.
	"""

	def __init__(self, root):
		"""
		Инициализация интерфейса.

		:param root: Окно приложения (tk.Tk).
		"""
		self.root = root
		self.root.title("LSL Maker Event")
		self.events = []  # Список полей ввода для событий
		self.buttons = []  # Список кнопок для отправки событий

		# Создание 5 строк с полями ввода и кнопками
		for i in range(5):
			event_label = tk.Label(root, text=f"Событие {i + 1}:")
			event_label.grid(row=i, column=0, padx=10, pady=5)

			event_entry = tk.Entry(root, width=30)
			event_entry.grid(row=i, column=1, padx=10, pady=5)
			self.events.append(event_entry)

			event_button = tk.Button(root, text="Отправить", command=lambda i=i: self.send_event(i))
			event_button.grid(row=i, column=2, padx=10, pady=5)
			self.buttons.append(event_button)

		# Кнопка выхода
		exit_button = tk.Button(root, text="Выход", command=root.quit)
		exit_button.grid(row=5, column=1, pady=10)

		# Создание LSL-потока
		self.create_lsl_stream()

	def create_lsl_stream(self):
		"""
		Создает LSL-поток для отправки маркеров.
		"""
		info = StreamInfo(name='LSLMakerEvent', type='Markers', channel_count=1, nominal_srate=0,
		                  channel_format='int32', source_id='myuidw43536')
		self.outlet = StreamOutlet(info)

	def send_event(self, event_index):
		"""
		Отправляет событие в LSL-поток.

		:param event_index: Индекс события (0-4).
		"""
		event_text = self.events[event_index].get()
		if event_text:
			self.outlet.push_sample([event_index + 1])  # Отправка маркера
			print(f"Событие '{event_text}' отправлено с маркером {event_index + 1}")

if __name__ == "__main__":
	root = tk.Tk()
	app = LSLMakerEventApp(root)
	root.mainloop()