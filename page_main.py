import tkinter as tk
import customtkinter
from tkinter import *
from tkinter.filedialog import askopenfile
import webbrowser
from PIL import Image


# Colors
gris_fonce = "#333333"
gris_moyen = "#C0C0C0"
gris_claire = "#CCCCCC"
blanc = "#FFFFFF"
bleu = "#003366"

window = Tk()
file = tk.Text(window)
file.grid()

# Code :
def open_link():
    webbrowser.open("https://github.com/Sinayel?tab=repositories")

def on_enter(event):
    BoutonPack["bg"] = blanc
    BoutonPack["fg"] = "#323232"

def on_leave(event):
    BoutonPack["bg"] = "#323232"
    BoutonPack["fg"] = blanc

def file():
    file = askopenfile(mode ='r', filetypes =[('Python Files', '*.py',)])
    if file is not None:
        content = file.read()
        print(content)
    pass

def on_click():
    print("you are in !")
    pass



# Main frames/blocks
topbar=tk.Frame(window, bg=bleu)
topbar.place(relx=0, rely=0, relwidth=1, relheight=0.08)

mainFrame=tk.Frame(window, bg=gris_moyen)
mainFrame.place(relx=0.15, rely=0.08, relwidth=1, relheight=0.92)

southBar=tk.Frame(window, bg=blanc)
southBar.place(relx=0, rely=0.08, relwidth=0.15, relheight=1)

#   Tous les Buttons

# Topbar Contents
reportBug=customtkinter.CTkButton(topbar, text="  GitHub", anchor="w", font=("Futura PT", 13), command=open_link)
reportBug.place(relx=0.9, rely=0.2, relwidth=0.085, relheight=0.55)


# Main content
BoutonFile=customtkinter.CTkButton(mainFrame, text="📂", font=("Futura PT", 30), command=file)
BoutonFile.place(relx=0.06, rely=0.05, relwidth=0.1, relheight=0.08)


# Créer un label pour l'effet visuel du bouton
BoutonPack = tk.Label(mainFrame, text=" appliquer", font=("Futura PT", 15))
BoutonPack.bind("<Enter>", on_enter)
BoutonPack.bind("<Leave>", on_leave)
BoutonPack.bind("<Button-1>", lambda event: on_click())
BoutonPack.place(relx=0.06, rely=0.15, relwidth=0.1, relheight=0.046)


# Personalization
window.resizable(width=False, height=False)
window.configure(bg=blanc)

window.title("MTS")
window.geometry('830x500')
window.update()
window.mainloop()
