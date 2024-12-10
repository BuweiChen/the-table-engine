import tkinter as tk
from tkinter import filedialog, messagebox, ttk
from PIL import Image, ImageTk


class AddItemPopup(tk.Toplevel):
    def __init__(self, parent, title, item_type, existing_data=None):
        super().__init__(parent)
        self.parent = parent
        self.item_type = item_type  # "structure" or "entity"
        self.existing_data = existing_data
        self.title(title)
        self.geometry("400x400")

        tk.Label(self, text="Name:").pack(anchor="w", padx=10, pady=5)
        self.name_var = tk.StringVar()
        self.name_entry = tk.Entry(self, textvariable=self.name_var)
        self.name_entry.pack(fill="x", padx=10)

        tk.Label(self, text="Bitmap File (BMP):").pack(anchor="w", padx=10, pady=5)
        self.file_var = tk.StringVar()
        file_frame = tk.Frame(self)
        file_frame.pack(fill="x", padx=10)
        self.file_entry = tk.Entry(file_frame, textvariable=self.file_var)
        self.file_entry.pack(side="left", fill="x", expand=True)
        tk.Button(file_frame, text="Browse", command=self.browse_file).pack(side="left")

        tk.Label(self, text="Columns:").pack(anchor="w", padx=10, pady=5)
        self.cols_var = tk.IntVar(value=1)
        tk.Entry(self, textvariable=self.cols_var).pack(fill="x", padx=10)

        tk.Label(self, text="Rows:").pack(anchor="w", padx=10, pady=5)
        self.rows_var = tk.IntVar(value=1)
        tk.Entry(self, textvariable=self.rows_var).pack(fill="x", padx=10)

        tk.Label(self, text="Sprite Length (px):").pack(anchor="w", padx=10, pady=5)
        self.length_var = tk.IntVar(value=64)
        tk.Entry(self, textvariable=self.length_var).pack(fill="x", padx=10)

        btn_frame = tk.Frame(self)
        btn_frame.pack(fill="x", pady=10)
        tk.Button(btn_frame, text="OK", command=self.confirm).pack(
            side="right", padx=10
        )
        tk.Button(btn_frame, text="Cancel", command=self.destroy).pack(side="right")

        # If editing existing data
        if self.existing_data:
            self.name_var.set(self.existing_data["name"])
            self.file_var.set(self.existing_data["file"])
            self.cols_var.set(self.existing_data["columns"])
            self.rows_var.set(self.existing_data["rows"])
            self.length_var.set(self.existing_data["length"])

    def browse_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("BMP Files", "*.bmp")])
        if file_path:
            self.file_var.set(file_path)

    def confirm(self):
        name = self.name_var.get()
        file = self.file_var.get()
        cols = self.cols_var.get()
        rows = self.rows_var.get()
        length = self.length_var.get()

        if not name or not file:
            messagebox.showwarning(
                "Incomplete", "Please provide a name and a bmp file."
            )
            return

        # Load the BMP and slice into frames
        try:
            img = Image.open(file)
        except Exception as e:
            messagebox.showerror("Error", f"Failed to load image: {e}")
            return

        w, h = img.size
        frame_width = w // cols
        frame_height = h // rows

        # Scale frames to 'length'
        scale = length / frame_width
        new_width = int(frame_width * scale)
        new_height = int(frame_height * scale)

        frames = []
        for r in range(rows):
            for c in range(cols):
                frame = img.crop(
                    (
                        c * frame_width,
                        r * frame_height,
                        (c + 1) * frame_width,
                        (r + 1) * frame_height,
                    )
                )
                frame = frame.resize((new_width, new_height), Image.LANCZOS)
                frames.append(ImageTk.PhotoImage(frame))

        data = {
            "name": name,
            "file": file,
            "columns": cols,
            "rows": rows,
            "length": length,
            "frames": frames,
        }

        self.parent.add_item_callback(
            self.item_type, data, self.existing_data is not None
        )
        self.destroy()


class LevelEditorApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Level Editor")
        self.geometry("1200x900")
        self.popup_window = None

        # Data storage
        self.structures = {}  # name -> data dict
        self.entities = {}  # name -> data dict
        self.levels = []  # list of dict { "canvas": canvas_widget, "items": [(item_name, x, y, image_id), ...] }

        self.current_level_index = -1

        # Frames
        self.left_frame = tk.Frame(self, width=200, bg="#ddd")
        self.left_frame.pack(side="left", fill="y")

        # Structures UI
        tk.Label(
            self.left_frame, text="Structures", font=("Arial", 14, "bold"), bg="#ddd"
        ).pack(anchor="nw", padx=5, pady=5)
        btn_frame_struct = tk.Frame(self.left_frame, bg="#ddd")
        btn_frame_struct.pack(fill="x")
        tk.Button(
            btn_frame_struct,
            text="Add",
            command=lambda: self.show_add_popup("structure"),
        ).pack(side="left", padx=5, pady=5)
        tk.Button(
            btn_frame_struct, text="Delete", command=self.delete_selected_structure
        ).pack(side="left", padx=5, pady=5)
        self.structures_listbox = tk.Listbox(self.left_frame)
        self.structures_listbox.pack(fill="both", expand=True, padx=5, pady=(0, 5))
        self.structures_listbox.bind(
            "<Double-Button-1>", lambda e: self.edit_selected_item("structure")
        )

        # Entities UI
        tk.Label(
            self.left_frame, text="Entities", font=("Arial", 14, "bold"), bg="#ddd"
        ).pack(anchor="nw", padx=5, pady=5)
        btn_frame_entity = tk.Frame(self.left_frame, bg="#ddd")
        btn_frame_entity.pack(fill="x")
        tk.Button(
            btn_frame_entity, text="Add", command=lambda: self.show_add_popup("entity")
        ).pack(side="left", padx=5, pady=5)
        tk.Button(
            btn_frame_entity, text="Delete", command=self.delete_selected_entity
        ).pack(side="left", padx=5, pady=5)
        self.entities_listbox = tk.Listbox(self.left_frame)
        self.entities_listbox.pack(fill="both", expand=True, padx=5, pady=(0, 5))
        self.entities_listbox.bind(
            "<Double-Button-1>", lambda e: self.edit_selected_item("entity")
        )

        # Drag and drop setup
        self.drag_data = {"type": None, "name": None, "item_index": None, "image": None}
        self.bind("<ButtonRelease-1>", self.on_mouse_release)
        self.bind("<Motion>", self.on_mouse_move)
        self.left_frame.bind_all("<B1-Motion>", self.on_mouse_drag)
        self.entities_listbox.bind("<Button-1>", lambda e: self.start_drag("entity", e))
        self.structures_listbox.bind(
            "<Button-1>", lambda e: self.start_drag("structure", e)
        )

        # Right Frame for levels
        self.right_frame = tk.Frame(self, width=200, bg="#ddd")
        self.right_frame.pack(side="right", fill="y")
        tk.Label(
            self.right_frame, text="Levels", font=("Arial", 14, "bold"), bg="#ddd"
        ).pack(anchor="nw", padx=5, pady=5)
        btn_frame_levels = tk.Frame(self.right_frame, bg="#ddd")
        btn_frame_levels.pack(fill="x", padx=5, pady=5)
        tk.Button(btn_frame_levels, text="Add", command=self.add_level).pack(
            side="left", padx=5
        )
        tk.Button(
            btn_frame_levels, text="Delete", command=self.delete_selected_level
        ).pack(side="left", padx=5)

        self.levels_listbox = tk.Listbox(self.right_frame)
        self.levels_listbox.pack(fill="both", expand=True, padx=5, pady=(0, 5))
        self.levels_listbox.bind("<<ListboxSelect>>", lambda e: self.switch_level())

        # Main Canvas Frame (for levels)
        self.center_frame = tk.Frame(self, bg="#eee", width=800, height=800)
        self.center_frame.pack(side="left", fill="both", expand=True)
        self.center_frame.pack_propagate(False)

        # Initially add one level
        self.add_level()

    def add_item_callback(self, item_type, data, editing=False):
        """Called when popup confirms adding/editing an item."""
        if item_type == "structure":
            if editing:
                sel = self.structures_listbox.curselection()
                if sel:
                    old_name = self.structures_listbox.get(sel[0])
                    del self.structures[old_name]
                    self.structures_listbox.delete(sel[0])
            name = data["name"]
            self.structures[name] = data
            self.structures_listbox.insert("end", name)

        else:  # entity
            if editing:
                sel = self.entities_listbox.curselection()
                if sel:
                    old_name = self.entities_listbox.get(sel[0])
                    del self.entities[old_name]
                    self.entities_listbox.delete(sel[0])
            name = data["name"]
            self.entities[name] = data
            self.entities_listbox.insert("end", name)

    def show_add_popup(self, item_type):
        if self.popup_window and self.popup_window.winfo_exists():
            return
        self.popup_window = AddItemPopup(
            self, f"Add {item_type.capitalize()}", item_type
        )
        self.popup_window.protocol("WM_DELETE_WINDOW", self.on_popup_close)

    def edit_selected_item(self, item_type):
        if self.popup_window and self.popup_window.winfo_exists():
            return

        if item_type == "structure":
            sel = self.structures_listbox.curselection()
            if not sel:
                return
            name = self.structures_listbox.get(sel[0])
            data = self.structures[name]
        else:
            sel = self.entities_listbox.curselection()
            if not sel:
                return
            name = self.entities_listbox.get(sel[0])
            data = self.entities[name]

        self.popup_window = AddItemPopup(
            self, f"Edit {item_type.capitalize()}", item_type, existing_data=data
        )
        self.popup_window.protocol("WM_DELETE_WINDOW", self.on_popup_close)

    def delete_selected_structure(self):
        sel = self.structures_listbox.curselection()
        if not sel:
            return
        name = self.structures_listbox.get(sel[0])
        del self.structures[name]
        self.structures_listbox.delete(sel[0])
        self.remove_all_instances(name)

    def delete_selected_entity(self):
        sel = self.entities_listbox.curselection()
        if not sel:
            return
        name = self.entities_listbox.get(sel[0])
        del self.entities[name]
        self.entities_listbox.delete(sel[0])
        self.remove_all_instances(name)

    def remove_all_instances(self, name):
        """Remove all instances of the given structure/entity from all levels."""
        for level_data in self.levels:
            new_items = []
            for itm_name, x, y, img_id in level_data["items"]:
                if itm_name == name:
                    level_data["canvas"].delete(img_id)
                else:
                    new_items.append((itm_name, x, y, img_id))
            level_data["items"] = new_items

    def start_drag(self, item_type, event):
        listbox = (
            self.structures_listbox
            if item_type == "structure"
            else self.entities_listbox
        )
        index = listbox.nearest(event.y)
        if index < 0:
            return
        name = listbox.get(index)

        self.drag_data["type"] = item_type
        self.drag_data["name"] = name
        self.drag_data["item_index"] = index

        if item_type == "structure":
            frames = self.structures[name]["frames"]
        else:
            frames = self.entities[name]["frames"]

        self.drag_data["image"] = frames[0] if frames else None
        self.drag_data["image_id"] = None  # Initialize the image ID for temporary image

    def on_mouse_drag(self, event):
        if self.drag_data["type"]:
            canvas = self.levels[self.current_level_index]["canvas"]
            x = event.x_root - canvas.winfo_rootx()
            y = event.y_root - canvas.winfo_rooty()
            if self.drag_data.get("image_id"):
                canvas.coords(self.drag_data["image_id"], x, y)
            else:
                # Create a temporary image centered at the cursor
                self.drag_data["image_id"] = canvas.create_image(
                    x, y, image=self.drag_data["image"], anchor="center"
                )
                
    def on_mouse_move(self, event):
        # level_data = self.levels[self.current_level_index]
        # print(len(level_data["items"]))

    def on_mouse_release(self, event):
        if self.drag_data["type"]:
            if self.current_level_index >= 0:
                level_data = self.levels[self.current_level_index]
                canvas = level_data["canvas"]
                canvas_x = event.x_root - canvas.winfo_rootx()
                canvas_y = event.y_root - canvas.winfo_rooty()

                if 0 <= canvas_x <= 800 and 0 <= canvas_y <= 800:
                    # Create the final image at the release position
                    img_id = canvas.create_image(
                        canvas_x,
                        canvas_y,
                        image=self.drag_data["image"],
                        anchor="center",
                    )
                    level_data["items"].append(
                        (self.drag_data["name"], canvas_x, canvas_y, img_id)
                    )

            # Remove the temporary image
            canvas = self.levels[self.current_level_index]["canvas"]
            if self.drag_data.get("image_id"):
                canvas.delete(self.drag_data["image_id"])

            # Reset drag data
            self.drag_data = {
                "type": None,
                "name": None,
                "item_index": None,
                "image": None,
                "image_id": None,
            }

    def add_level(self):
        canvas = tk.Canvas(self.center_frame, bg="white", width=800, height=800)
        # Draw grid
        for x in range(0, 801, 40):
            canvas.create_line(x, 0, x, 800, fill="#ccc")
        for y in range(0, 801, 40):
            canvas.create_line(0, y, 800, y, fill="#ccc")

        # Place the canvas
        canvas.place(x=0, y=0)
        level_index = len(self.levels)
        self.levels.append({"canvas": canvas, "items": []})
        self.levels_listbox.insert("end", f"Level {level_index+1}")

        # If this is the first level, select and show it
        if self.current_level_index == -1:
            self.levels_listbox.selection_clear(0, "end")
            self.levels_listbox.selection_set(0)
            self.switch_level()
        else:
            # For subsequent levels, they start below the currently shown level.
            # We'll lower them until switched to.
            canvas.lower()

    def delete_selected_level(self):
        sel = self.levels_listbox.curselection()
        if not sel:
            return
        idx = sel[0]
        level_data = self.levels[idx]
        level_data["canvas"].destroy()
        del self.levels[idx]
        self.levels_listbox.delete(idx)

        # Rename levels
        for i in range(len(self.levels)):
            self.levels_listbox.delete(i)
            self.levels_listbox.insert(i, f"Level {i+1}")

        if len(self.levels) == 0:
            self.current_level_index = -1
        else:
            new_idx = min(idx, len(self.levels) - 1)
            self.levels_listbox.selection_clear(0, "end")
            self.levels_listbox.selection_set(new_idx)
            self.switch_level()

    def switch_level(self):
        sel = self.levels_listbox.curselection()
        print(sel)
        if not sel:
            return
        idx = sel[0]
        # Hide old level canvas
        if self.current_level_index >= 0:
            old_canvas = self.levels[self.current_level_index]["canvas"]
            old_canvas.lower(self.center_frame)

        # Show new level canvas
        self.current_level_index = idx
        new_canvas = self.levels[idx]["canvas"]
        new_canvas.tkraise  # Use tkraise() instead of lift()

    def on_popup_close(self):
        # Add your cleanup code here
        self.popup_window.destroy()


if __name__ == "__main__":
    app = LevelEditorApp()
    app.mainloop()
