import matplotlib
matplotlib.use("Agg") # run on headless server
import matplotlib.pyplot as plt
import numpy as np
import csv
import os
import argparse

def add_line(category_node,arr,line,level):
    if level == (len(arr) - 1):
        data = category_node.get("data")
        if data is None:
            data = []
            category_node["data"]=data
        data.append(line)
    else:
        node = category_node.get(arr[level])
        if node is None:
            node = {}
            category_node[arr[level]]=node
        add_line(node,arr,line,level+1)

def plot_benchmark_results():
    global args
    full_path = args.input_file

    with open(full_path, 'rt') as f:
        global xcount
        title = "benchmark"
        csv_reader = csv.reader(f)
        depth = None
        got_header = False
        header_lines = []
        column_names = None
        body_lines = []
        category_map = {}
        for line in csv_reader:
            if got_header == False:
                if isinstance(line,list) and line[0]=="name":
                    column_names = line
                    got_header = True
                else:
                    header_lines.append(line)
            else:
                converted = []
                for x in line:
                    if len(x)>0 and x[0] in "-0123456789":
                        if '.' in x:
                            converted.append(float(x))
                        else:
                            converted.append(int(x))
                    else:
                        converted.append(x)
                body_lines.append(converted)
        for line in body_lines:
            name = line[0]
            if "_BigO" in name or "_RMS" in name:
                continue
            if args.ignore_name is not None:
                if args.ignore_name in name:
                    continue
            arr= name.replace("_v","|v").replace("<","|").replace(">","").replace("/","|").split("|")
            depth=len(arr)
            if len(arr)>3:
                swap = [arr[0],arr[2],arr[1],arr[3]]
                add_line(category_map,swap,line,0)
        if depth == 4:
            title= "benchmark"
            ycount=1
            for k in category_map.keys():
                title = k
                category_map = category_map[k]
                break
            xcount = len(category_map.keys())
            fig, axs = plt.subplots(xcount, ycount, sharex=True)
            for ik, key in enumerate(category_map.keys()):
                plot_row(category_map[key],ik,0,key,axs,title)
        fig2 = plt.gcf()
        #plt.show()
        file_format="png"
        output_file_name = args.input_file.replace(".csv","")
        if args.ignore_name is not None:
            output_file_name = output_file_name + "_ignore_" + args.ignore_name
        output_file_name = output_file_name + ".png"
        fig2.savefig(output_file_name,
                    dpi=100,
                    format=file_format,
                    quality=100)

def plot_row(node,row_count,col_count,row_title,axs,grid_title):
    legend_handles = []
    for ik,key in enumerate(node.keys()):
        plot_graph(node[key],row_count,ik,row_title,key,axs,grid_title)
        legend_handles.append(key)
    plt.legend(legend_handles)
    plt.ylabel("cpu time (ns)")
    plt.xlabel("bits in input")

def plot_graph(node,row_count,col_count,row_title,graph_title, axs,grid_title):
    global xcount
    for ik,key in enumerate(node.keys()):
        plot_series(node[key],row_count,col_count,ik, graph_title, axs)

    if xcount == 1:
        axs.set_title(grid_title + " - " + row_title)
    else:
        axs[row_count].set_title(grid_title + " - " + row_title)

def plot_series(data,row_count,col_count,series_count,series_title, axs):
    global xcount
    if data is not None:
        x_values = []
        y_values = []
        for ipoint,point in enumerate(data):
            x_value = ipoint
            arr = point[0].split("/")
            try:
                y_value = int(point[3]) # cpu time
                y_values.append(y_value)
                if len(arr)>1:
                    x_value = int(arr[1])
                    x_values.append(x_value)
            except ValueError:
                # no data point but still need to add something to ensure there is a series
                y_value = -1
                y_values.append(y_value)
                if len(arr)>1:
                    x_value = int(arr[1])
                    x_values.append(x_value)
        # if the entire series is made of -1s, truncate it to origin.
        all_nulls = True
        for y in y_values:
            if not y == -1:
                all_nulls = False
        if all_nulls:
            x_tidied = [0]
            y_tidied = [0]
        else:
            # remove any null values from valid series (insert a gap)
            x_tidied = []
            y_tidied = []
            for i,y in enumerate(y_values):
                if not y == -1:
                    y_tidied.append(y)
                    x_tidied.append(x_values[i])


        if len(x_tidied)>0 and len(y_tidied)>0 and len(x_tidied)==len(y_tidied):
            if xcount == 1:
                handle, = axs.plot(np.array(x_tidied), np.array(y_tidied), label=series_title, marker='.', linestyle='--')
            else:
                handle, = axs[row_count].plot(np.array(x_tidied), np.array(y_tidied), label=series_title, marker='.',
                                              linestyle='--')

def main():
    plot_benchmark_results()

if __name__ == "__main__":
    global args
    parser = argparse.ArgumentParser()
    requiredNamed = parser.add_argument_group('required named arguments')
    requiredNamed.add_argument('--input-file', help='full path to input filename')
    #requiredNamed.add_argument('--output-folder', help='full path to output folder')
    parser.add_argument('--ignore-name', help='do not plot this series (used to remove the baseline)')
    args = parser.parse_args()
    if args.input_file is None: #  or args.output_folder is None:
        parser.print_help()
    else:
        main()

