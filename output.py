import sys
import os
import tkinter as tk

n = -1
d = 500
buffer = 100

def _create_circle(self, x, y, r, **kwargs):
    x = x * d / (2.0 * n) + (d / 2.0) + buffer
    y = y * d / (2.0 * n) + (d / 2.0) + buffer
    return self.create_oval(x-r, y-r, x+r, y+r, **kwargs)
tk.Canvas.create_circle = _create_circle

def _create_line_scaled(self, x1, y1, x2, y2, **kwargs):
    x1 = x1 * d / (2.0 * n) + (d / 2.0) + buffer
    y1 = y1 * d / (2.0 * n) + (d / 2.0) + buffer
    x2 = x2 * d / (2.0 * n) + (d / 2.0) + buffer
    y2 = y2 * d / (2.0 * n) + (d / 2.0) + buffer
    return self.create_line(x1, y1, x2, y2, **kwargs)
tk.Canvas.create_line_scaled = _create_line_scaled

def main():
    global n, d
    if os.environ.get('DISPLAY','') == '':
        print('Cannot run on remote without display')
        return

    root = tk.Tk()

    f = open(sys.argv[1], "r")
    line = f.readline() # \n
    line = f.readline() # n points

    n = int(line.split(' ')[0])
    b_canvas = tk.Canvas(root, bg="white", height=d+2*buffer, width=d+2*buffer)
    b_canvas.create_line((d + (2*buffer))/2.0,0,(d + (2*buffer))/2.0,d+2*buffer, fill="gray", width=1) # x
    b_canvas.create_line(0, (d + (2*buffer))/2.0,d+2*buffer,(d + (2*buffer))/2.0, fill="gray", width=1) # y

    q_canvas = tk.Canvas(root, bg="white", height=d+2*buffer, width=d+2*buffer)
    q_canvas.create_line((d + (2*buffer))/2.0,0,(d + (2*buffer))/2.0,d+2*buffer, fill="gray", width=1) # x
    q_canvas.create_line(0, (d + (2*buffer))/2.0,d+2*buffer,(d + (2*buffer))/2.0, fill="gray", width=1) # y

    line = f.readline() # \n
    line = f.readline() # "Points:"
    line = f.readline() # (x,y)

    while line[0] != "B": # Brute Hull Time
        coords = line.split(',')
        b_canvas.create_circle(int(coords[0][1:]), int(coords[1][:-2]), 2, fill="black", outline="#FFFFFF", width=0)
        q_canvas.create_circle(int(coords[0][1:]), int(coords[1][:-2]), 2, fill="black", outline="#FFFFFF", width=0)
        line = f.readline()

    b_time = line.split('\t')[1]
    b_canvas.create_text(buffer*2, buffer/2, text="Brute Force Algorithm: %s" % b_time, fill="black", font=('Helvetica 15 bold'))

    line = f.readline() # \n
    line = f.readline() # Brute Hull:
    line = f.readline() # (x, y)
    prev_coords = "NULL"
    first_coords = "NULL"
    while line[0] != "Q": # Quick Hull Time
        coords = line.split(',')
        b_canvas.create_circle(int(coords[0][1:]), int(coords[1][:-2]), 2, fill="blue", outline="#FFFFFF", width=0)
        if (first_coords == "NULL"):
            first_coords = coords
            prev_coords = coords
        else:
            b_canvas.create_line_scaled(int(coords[0][1:]), int(coords[1][:-2]), int(prev_coords[0][1:]), int(prev_coords[1][:-2]), fill="red", width=1)
        line = f.readline()
        prev_coords = coords
    b_canvas.create_line_scaled(int(first_coords[0][1:]), int(first_coords[1][:-2]), int(prev_coords[0][1:]), int(prev_coords[1][:-2]), fill="red", width=1)

    b_canvas.pack(side = tk.LEFT)

    q_time = line.split('\t')[1]
    q_canvas.create_text(buffer*2, buffer/2, text="QuickHull Algorithm: %s" % q_time, fill="black", font=('Helvetica 15 bold'))

    line = f.readline() # \n
    line = f.readline() # Quick Hull:
    line = f.readline() # (x, y)

    prev_coords = "NULL"
    first_coords = "NULL"
    while line[0] != "b": # b_set.size()
        coords = line.split(',')
        q_canvas.create_circle(int(coords[0][1:]), int(coords[1][:-2]), 2, fill="blue", outline="#FFFFFF", width=0)
        if (first_coords == "NULL"):
            first_coords = coords
            prev_coords = coords
        else:
            q_canvas.create_line_scaled(int(coords[0][1:]), int(coords[1][:-2]), int(prev_coords[0][1:]), int(prev_coords[1][:-2]), fill="red", width=1)
        line = f.readline()
        prev_coords = coords
    q_canvas.create_line_scaled(int(first_coords[0][1:]), int(first_coords[1][:-2]), int(prev_coords[0][1:]), int(prev_coords[1][:-2]), fill="red", width=1)

    q_canvas.pack(side = tk.RIGHT)

    root.mainloop()
    return

main()