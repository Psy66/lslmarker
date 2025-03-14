# gui.py
import tkinter as tk
from pylsl import StreamInfo, StreamOutlet

class LSLMakerEventApp:
    """
    A class for creating a graphical interface for LSL Maker Event.
    Allows users to input event names and send them to an LSL stream.
    """

    def __init__(self, root):
        """
        Initializes the interface.

        :param root: The application window (tk.Tk).
        """
        self.root = root
        self.root.title("LSL Maker Event")
        self.events = []  # List of event input fields
        self.buttons = []  # List of buttons for sending events

        # Create 5 rows with event input fields and send buttons
        for i in range(5):
            event_label = tk.Label(root, text=f"Event {i + 1}:")
            event_label.grid(row=i, column=0, padx=10, pady=5)

            event_entry = tk.Entry(root, width=30)
            event_entry.grid(row=i, column=1, padx=10, pady=5)
            self.events.append(event_entry)

            event_button = tk.Button(root, text="Send", command=lambda i=i: self.send_event(i))
            event_button.grid(row=i, column=2, padx=10, pady=5)
            self.buttons.append(event_button)

        # Exit button
        exit_button = tk.Button(root, text="Exit", command=root.quit)
        exit_button.grid(row=5, column=1, pady=10)

        # Create an LSL stream
        self.create_lsl_stream()

    def create_lsl_stream(self):
        """
        Creates an LSL stream for sending markers.
        """
        info = StreamInfo(name='LSLMakerEvent', type='Markers', channel_count=1, nominal_srate=0,
                          channel_format='int32', source_id='myuidw43536')
        self.outlet = StreamOutlet(info)

    def send_event(self, event_index):
        """
        Sends an event to the LSL stream.

        :param event_index: The index of the event (0-4).
        """
        event_text = self.events[event_index].get()
        if event_text:
            self.outlet.push_sample([event_index + 1])  # Send the marker
            print(f"Event '{event_text}' sent with marker {event_index + 1}")

if __name__ == "__main__":
    root = tk.Tk()
    app = LSLMakerEventApp(root)
    root.mainloop()