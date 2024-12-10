import tkinter as tk
from tkinter import filedialog, messagebox, ttk
from PIL import Image, ImageTk
from backend import export_json

# Todo: flush out label for gameobject properties (includes type + any non-transform, non-texture properties (health, speed, etc.))
class AddPropertyPopup(tk.Toplevel):
    def __init__(self):
        super().__init__()
        self.title("Add Property")
        self.geometry("400x300")

        tk.Label(self, text="Property Name:").pack(anchor="w", padx=10, pady=5)
        self.name_var = tk.StringVar()
        self.name_entry = tk.Entry(self, textvariable=self.name_var)
        self.name_entry.pack(fill="x", padx=10)

        tk.Label(self, text="Property Type:").pack(anchor="w", padx=10, pady=5)
        self.type_var = tk.StringVar(value="int")
        self.type_entry = ttk.Combobox(
            self, textvariable=self.type_var, values=["int", "float", "str"]
        )
        self.type_entry.pack(fill="x", padx=10)

        tk.Label(self, text="Default Value:").pack(anchor="w", padx=10, pady=5)
        self.default_var = tk.StringVar()
        self.default_entry = tk.Entry(self, textvariable=self.default_var)
        self.default_entry.pack(fill="x", padx=10)

        btn_frame = tk.Frame(self)
        btn_frame.pack(fill="x", pady=10)
        tk.Button(btn_frame, text="OK", command=self.confirm).pack(side="right", padx=10)
        tk.Button(btn_frame, text="Cancel", command=self.destroy).pack(side="right")

    def confirm(self):
        name = self.name_var.get()
        prop_type = self.type_var.get()
        default = self.default_var.get()

        self.destroy()

    def destroy(self):
        return super().destroy()

class AddItemPopup(tk.Toplevel):
    def __init__(self, parent, title, item_type, existing_data=None):
        super().__init__(parent)
        self.parent = parent
        self.item_type = item_type  # "structure" or "entity"
        self.existing_data = existing_data
        self.title(title)
        self.geometry("700x650")

        self.cols_var = tk.IntVar(value=1)
        self.rows_var = tk.IntVar(value=1)
        self.length_var = tk.IntVar(value=32)
        self.width_var = tk.IntVar(value=32)
        self.top_left_x = tk.IntVar(value=0)
        self.top_left_y = tk.IntVar(value=0)
        self.size_width = tk.IntVar(value=0)
        self.size_height = tk.IntVar(value=0)

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
        tk.Entry(self, textvariable=self.cols_var).pack(fill="x", padx=10)
        self.cols_var.trace_add("write", lambda *args: self.preview_image(self.file_var.get()))

        tk.Label(self, text="Rows:").pack(anchor="w", padx=10, pady=5)
        tk.Entry(self, textvariable=self.rows_var).pack(fill="x", padx=10)
        self.rows_var.trace_add("write", lambda *args: self.preview_image(self.file_var.get()))

        screen_frame = tk.Frame(self)
        screen_frame.pack(fill="x", padx=10, pady=10)

        tk.Label(screen_frame, text="Screen width (px):").grid(row=0, column=0, sticky="w", padx=10, pady=5)
        tk.Entry(screen_frame, textvariable=self.length_var).grid(row=0, column=1, sticky="w", padx=10, pady=5)

        tk.Label(screen_frame, text="Screen height (px):").grid(row=0, column=2, sticky="e", padx=10, pady=5)
        tk.Entry(screen_frame, textvariable=self.width_var).grid(row=0, column=3, sticky="e", padx=10, pady=5)

         # image preview
        self.preview_canvas = tk.Canvas(self, width=200, height=200)
        self.preview_canvas.pack(fill="both", padx=20)

        # Create a frame to hold the form
        form_frame = tk.Frame(self)
        form_frame.pack(fill="x", padx=10, pady=10)

        # TopLeft X
        tk.Label(form_frame, text="Sprite X:").grid(row=0, column=0, sticky="w", padx=5, pady=5)
        tk.Entry(form_frame, textvariable=self.top_left_x).grid(row=0, column=1, sticky="w", padx=10, pady=5)
        self.top_left_x.trace_add("write", lambda *args: self.preview_image(self.file_var.get()))

        # TopLeft Y
        tk.Label(form_frame, text="Sprite Y:").grid(row=0, column=2, sticky="e", padx=5, pady=5)
        tk.Entry(form_frame, textvariable=self.top_left_y).grid(row=0, column=3, sticky="e", padx=10, pady=5)
        self.top_left_y.trace_add("write", lambda *args: self.preview_image(self.file_var.get()))

        # Size width
        tk.Label(form_frame, text="Sprite width (px):").grid(row=1, column=0, sticky="w", padx=5, pady=5)
        tk.Entry(form_frame, textvariable=self.size_width).grid(row=1, column=1, sticky="w", padx=10, pady=5)
        self.size_width.trace_add("write", lambda *args: self.preview_image(self.file_var.get()))

        # Size height
        tk.Label(form_frame, text="Sprite height (px):").grid(row=1, column=2, sticky="e", padx=5, pady=5)
        tk.Entry(form_frame, textvariable=self.size_height).grid(row=1, column=3, sticky="e", padx=10, pady=5)
        self.size_height.trace_add("write", lambda *args: self.preview_image(self.file_var.get()))

        btn_frame = tk.Frame(self)
        btn_frame.pack(fill="x", pady=10)
        tk.Button(btn_frame, text="GameObject Properties", command=self.open_entity_properties).pack(
            side="left", padx=10)
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
            self.top_left_x.set(self.existing_data["top_left_x"])
            self.top_left_y.set(self.existing_data["top_left_y"])
            self.size_width.set(self.existing_data["size_width"])
            self.size_height.set(self.existing_data["size_height"])
            self.length_var.set(self.existing_data["length"])
            self.width_var.set(self.existing_data["width"])

    def browse_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("BMP Files", "*.bmp")])
        if file_path:
            self.file_var.set(file_path)
            self.preview_image(file_path, True)

    def confirm(self):
        name = self.name_var.get()
        file = self.file_var.get()
        cols = self.cols_var.get()
        rows = self.rows_var.get()
        size_width = self.size_width.get()
        size_height = self.size_height.get()
        top_left_x = self.top_left_x.get()
        top_left_y = self.top_left_y.get()
        length = self.length_var.get()
        width = self.width_var.get()

        editing = self.existing_data is not None

        if editing:
            old_name = self.existing_data["name"] if self.existing_data else ""
            if name != old_name and name in self.parent.structures:
                messagebox.showerror("Error", "A structure with that name already exists.")
                return
            elif name in self.parent.entities:
                messagebox.showerror("Error", "An entity with that name already exists.")
        elif name in self.parent.structures:
            messagebox.showerror("Error", "A structure with that name already exists.")
            return

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

        frame_width = size_width // cols
        frame_height = size_height // rows

        frames = []
        for r in range(rows):
            for c in range(cols):
                frame = img.crop(
                    (
                        c * frame_width + top_left_x,
                        r * frame_height + top_left_y,
                        (c + 1) * frame_width + top_left_x,
                        (r + 1) * frame_height + top_left_y,
                    )
                )

                frame = frame.resize((length, width), Image.LANCZOS)
                frames.append(ImageTk.PhotoImage(frame))

        data = {
            "name": name,
            "file": file,
            "columns": cols,
            "rows": rows,
            "length": length,
            "width": width,
            "top_left_x": top_left_x,
            "top_left_y": top_left_y,
            "size_width": size_width,
            "size_height": size_height,
            "frames": frames,
        }

        self.parent.add_item_callback(
            self.item_type, data, self.existing_data is not None
        )
        self.destroy()

    def preview_image(self, file_path, reset=False):
        # add red grid lines based on cols and rows by defautl set both to 1

        cols, rows = 1, 1
        size_width, size_height = 0, 0
        top_left_x, top_left_y = 0, 0

        try:
            if not reset:
                cols = int(self.cols_var.get())
                rows = int(self.rows_var.get())
                top_left_x = self.top_left_x.get()
                top_left_y = self.top_left_y.get()
                size_width = int(self.size_width.get())
                size_height = int(self.size_height.get())
            else:
                self.cols_var.set(1)
                self.rows_var.set(1)
                self.top_left_x.set(0)
                self.top_left_y.set(0)
                self.size_width.set(0)
                self.size_height.set(0)
        except:
            return
        
        try:
            img = Image.open(file_path)
            if size_width == 0:
                self.size_width.set(img.width)  
            if size_height == 0:
                self.size_height.set(img.height)                
            w, h = img.size
            if w > h:
                self.scale = 200 / w
            else:
                self.scale = 200 / h

            size_width = self.size_width.get() * self.scale
            size_height = self.size_height.get() * self.scale
            top_left_x = self.top_left_x.get() * self.scale
            top_left_y = self.top_left_y.get() * self.scale

            img = img.resize((int(w*self.scale), int(h*self.scale)), Image.LANCZOS)
            img_tk = ImageTk.PhotoImage(img)
            self.preview_canvas.delete("all")

            # anchor to the center of the canvas
            self.preview_canvas.create_image(0, 0, anchor="nw", image=img_tk)
            self.preview_canvas.image = img_tk

            w, h = img.size
            self.preview_canvas.create_line(top_left_x, top_left_y, top_left_x, top_left_y + size_height, fill="blue", width=3)
            self.preview_canvas.create_line(top_left_x + size_width, top_left_y, top_left_x + size_width, top_left_y + size_height, fill="blue", width=3)

            self.preview_canvas.create_line(top_left_x, top_left_y, top_left_x + size_width, top_left_y, fill="blue", width=3)
            self.preview_canvas.create_line(top_left_x, top_left_y + size_height, top_left_x + size_width, top_left_y + size_height, fill="blue", width=3)

            # Draw vertical lines
            for col in range(1, cols):
                dx = (size_width * col) // cols
                self.preview_canvas.create_line(top_left_x + dx, top_left_y, top_left_x + dx, top_left_y + size_height, fill="red", width=1)

            # Draw horizontal lines
            for row in range(1, rows):
                dy = (size_height * row // rows)
                self.preview_canvas.create_line(top_left_x, top_left_y + dy, top_left_x + size_width, top_left_y + dy, fill="red", width=1)

        except Exception as e:
            messagebox.showerror("Error", f"Failed to load image: {e}")

    # Todo: add GameObject Properties - type + specific properties (health, speed, etc.) depending on type
    def open_entity_properties(self):
        if self.file_var.get() == "":
            messagebox.showerror("Error", "Please select a file first.")
            return
        
        self.entity_properties = AddPropertyPopup()
        self.entity_properties.protocol("WM_DELETE_WINDOW", self.on_popup_close)

    def on_popup_close(self):
        self.entity_properties.destroy()

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

        # Menu Bar
        self.menubar = tk.Menu(self)

        # File
        self.file = tk.Menu(self.menubar, tearoff=0)
        self.menubar.add_cascade(label="File", menu=self.file)
        self.file.add_command(label="Export", command=None)

        self.config(menu=self.menubar)

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

        # Top Right Frame for levels
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
        self.popup_window.protocol("WM_DELETE_WINDOW")

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

            # Get raw coordinates relative to the canvas
            canvas_x = event.x_root - canvas.winfo_rootx()
            canvas_y = event.y_root - canvas.winfo_rooty()

            # Get the object's specified size
            if self.drag_data["type"] == "structure":
                obj_data = self.structures[self.drag_data["name"]]
            else:
                obj_data = self.entities[self.drag_data["name"]]

            # Calculate top-right alignment for the image
            snapped_x = canvas_x
            snapped_y = canvas_y  # No vertical offset for top-right alignment

            # Create or update the temporary image
            if self.drag_data.get("image_id"):
                canvas.coords(self.drag_data["image_id"], snapped_x, snapped_y)
            else:
                self.drag_data["image_id"] = canvas.create_image(
                    snapped_x, snapped_y, image=self.drag_data["image"], anchor="nw"
                )

    def on_mouse_move(self, event):
        # level_data = self.levels[self.current_level_index]
        # print(len(level_data["items"]))
        pass

    def on_mouse_release(self, event):
        if self.drag_data["type"]:
            if self.current_level_index >= 0:
                level_data = self.levels[self.current_level_index]
                canvas = level_data["canvas"]

                # Get raw coordinates relative to the canvas
                canvas_x = event.x_root - canvas.winfo_rootx()
                canvas_y = event.y_root - canvas.winfo_rooty()

                # Get the object's specified size
                if self.drag_data["type"] == "structure":
                    obj_data = self.structures[self.drag_data["name"]]
                else:
                    obj_data = self.entities[self.drag_data["name"]]

                # Snap to the nearest grid point (align top-right corner of image)
                grid_size = 32
                snapped_x = round(canvas_x / grid_size) * grid_size
                snapped_y = round(canvas_y / grid_size) * grid_size

                # Ensure snapped coordinates are within bounds
                if 0 <= snapped_x <= 800 and 0 <= snapped_y <= 800:
                    # Place the final image at the snapped position
                    img_id = canvas.create_image(
                        snapped_x, snapped_y, image=self.drag_data["image"], anchor="nw"
                    )
                    level_data["items"].append(
                        (self.drag_data["name"], snapped_x, snapped_y, img_id)
                    )

                # Remove the temporary drag image
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
        level_frame = tk.Frame(self.center_frame, width=800, height=800, bg="white")
        level_frame.place(x=0, y=0)
        canvas = tk.Canvas(level_frame, bg="white", width=800, height=800)
        canvas.pack(fill="both", expand=True)

        # Draw grid
        for x in range(0, 801, 32):
            canvas.create_line(x, 0, x, 800, fill="#ccc")
        for y in range(0, 801, 32):
            canvas.create_line(0, y, 800, y, fill="#ccc")

        self.levels.append({"frame": level_frame, "canvas": canvas, "items": []})
        self.levels_listbox.insert("end", f"Level {len(self.levels)}")

        new_idx = len(self.levels) - 1
        self.levels_listbox.selection_set(new_idx)
        self.switch_level()
        self.current_level_index = new_idx

    def switch_level(self):
        sel = self.levels_listbox.curselection()
        if not sel:
            return
        idx = sel[0]
        new_frame = self.levels[idx]["frame"]
        new_frame.tkraise()
        self.current_level_index = idx

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

    def export():
        export_json()


if __name__ == "__main__":
    app = LevelEditorApp()
    app.mainloop()
