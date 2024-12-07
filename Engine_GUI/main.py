import tkinter as tk
from tkinter import filedialog, messagebox, ttk

class LevelEditorApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Level Editor")
        self.geometry("1200x800")

        # Top-level frames
        # Left panel: Objects list
        self.left_frame = tk.Frame(self, width=200, bg="#ddd")
        self.left_frame.pack(side="left", fill="y")

        # Center panel: Map editor canvas
        self.center_frame = tk.Frame(self, bg="#eee")
        self.center_frame.pack(side="left", fill="both", expand=True)

        # Right panel: Levels/Waves
        self.right_frame = tk.Frame(self, width=200, bg="#ddd")
        self.right_frame.pack(side="right", fill="y")

        # Bottom panel: Properties and Script Editor
        self.bottom_frame = tk.Frame(self, height=200, bg="#ccc")
        self.bottom_frame.pack(side="bottom", fill="x")

        # Layout within the left frame: Objects list
        tk.Label(self.left_frame, text="Objects", font=("Arial", 14, "bold"), bg="#ddd").pack(anchor="nw", padx=5, pady=5)
        self.objects_listbox = tk.Listbox(self.left_frame)
        self.objects_listbox.pack(fill="both", expand=True, padx=5, pady=(0,5))
        # Example items
        for obj_name in ["Box", "Fence", "Wall", "Enemy", "Player", "Chest"]:
            self.objects_listbox.insert("end", obj_name)

        # Layout within the right frame: Levels and Waves
        # We can use tabs or separate labels to mimic the conceptual design
        self.right_top_frame = tk.Frame(self.right_frame, bg="#ddd")
        self.right_top_frame.pack(side="top", fill="both", expand=True)

        tk.Label(self.right_top_frame, text="Levels/Waves", font=("Arial", 14, "bold"), bg="#ddd").pack(anchor="nw", padx=5, pady=5)

        # Just placeholder frames or lists for levels/waves
        self.levels_label = tk.Label(self.right_top_frame, text="Levels:", bg="#ddd")
        self.levels_label.pack(anchor="nw", padx=5)
        self.levels_listbox = tk.Listbox(self.right_top_frame, height=5)
        self.levels_listbox.pack(fill="x", padx=5)
        for i in range(1,6):
            self.levels_listbox.insert("end", f"Level {i}")

        self.waves_label = tk.Label(self.right_top_frame, text="Waves:", bg="#ddd")
        self.waves_label.pack(anchor="nw", padx=5, pady=(10,0))
        self.waves_listbox = tk.Listbox(self.right_top_frame, height=5)
        self.waves_listbox.pack(fill="x", padx=5, pady=(0,5))
        for w in range(1,4):
            self.waves_listbox.insert("end", f"Wave {w}")

        # Center frame: Map (Canvas)
        self.map_canvas = tk.Canvas(self.center_frame, bg="white")
        self.map_canvas.pack(fill="both", expand=True, padx=5, pady=5)
        # Example: draw a grid or placeholder shapes
        for x in range(0, 800, 40):
            self.map_canvas.create_line(x, 0, x, 600, fill="#ccc")
        for y in range(0, 600, 40):
            self.map_canvas.create_line(0, y, 800, y, fill="#ccc")

        # Middle: Properties
        bottom_middle_frame = tk.Frame(self.bottom_frame, bg="#ccc")
        bottom_middle_frame.pack(side="left", fill="both", expand=True, padx=5, pady=5)

        tk.Label(bottom_middle_frame, text="Properties:", bg="#ccc").pack(anchor="nw", padx=5, pady=5)
        # Just some placeholder properties
        tk.Label(bottom_middle_frame, text="Sprite NPC:", bg="#ccc").pack(anchor="w", padx=5, pady=2)
        tk.Entry(bottom_middle_frame).pack(anchor="w", padx=5, pady=2)

        tk.Label(bottom_middle_frame, text="# Frames:", bg="#ccc").pack(anchor="w", padx=5, pady=2)
        tk.Entry(bottom_middle_frame).pack(anchor="w", padx=5, pady=2)

        tk.Label(bottom_middle_frame, text="Time to animate:", bg="#ccc").pack(anchor="w", padx=5, pady=2)
        tk.Entry(bottom_middle_frame).pack(anchor="w", padx=5, pady=2)

        tk.Label(bottom_middle_frame, text="Is pathable:", bg="#ccc").pack(anchor="w", padx=5, pady=2)
        tk.Checkbutton(bottom_middle_frame, bg="#ccc").pack(anchor="w", padx=5, pady=2)


    def load_file(self):
        file_path = filedialog.askopenfilename(title="Select a File")
        if file_path:
            messagebox.showinfo("File Selected", f"You selected {file_path}")

    def add_level(self):
        return




if __name__ == "__main__":
    app = LevelEditorApp()
    app.mainloop()
