from matplotlib import pyplot as plt
import os

repeat_times = 1000

class type_data:
    def __init__(self, name, bin_serialize, bin_deserialize, xml_serialize, xml_deserialize):
        self.name = name
        self.bin_serialize = bin_serialize
        self.bin_deserialize = bin_deserialize
        self.xml_serialize = xml_serialize
        self.xml_deserialize = xml_deserialize
        
class size_data:
    def __init__(self, name, bin_data, xml_data):
        self.name = name
        self.bin_serialize = []
        self.bin_deserialize = []
        self.xml_serialize = []
        self.xml_deserialize = []
        self.size = []
        
        for i in bin_data.split(" "):
            a, b = i.split("|")
            self.bin_serialize.append(float(a) * 1000 / repeat_times)
            self.bin_deserialize.append(float(b) * 1000 / repeat_times)
        for i in xml_data.split(" "):
            a, b = i.split("|")
            self.xml_serialize.append(float(a) * 1000 / repeat_times)
            self.xml_deserialize.append(float(b) * 1000 / repeat_times)
        start_size = 10 * 8
        for i in range(len(self.bin_serialize)):
            self.size.append(start_size)
            start_size *= 10

if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    print("start eval")
    
    bin_file_path = "../record/bin.txt"
    xml_file_path = "../record/xml.txt"
    
    bin_file = open(bin_file_path, "r")
    xml_file = open(xml_file_path, "r")
    
    # show type evaluation`
    type_bin_data = []
    type_xml_data = []
    line = bin_file.readline()
    while (line != "===\n"):
        type_bin_data.append(float(line.split(": ")[1]))
        line = bin_file.readline()
    line = xml_file.readline()
    while (line != "===\n"):
        type_xml_data.append(float(line.split(": ")[1]))
        line = xml_file.readline()
    type_item = []
    type_item.append(type_data("bool", type_bin_data[0] / repeat_times * 1000, type_bin_data[1] / repeat_times * 1000, type_xml_data[0] / repeat_times * 1000, type_xml_data[1] / repeat_times * 1000))
    type_item.append(type_data("char", type_bin_data[2] / repeat_times * 1000, type_bin_data[3] / repeat_times * 1000, type_xml_data[2] / repeat_times * 1000, type_xml_data[3] / repeat_times * 1000))
    type_item.append(type_data("int", type_bin_data[4] / repeat_times * 1000, type_bin_data[5] / repeat_times * 1000, type_xml_data[4] / repeat_times * 1000, type_xml_data[5] / repeat_times * 1000))
    type_item.append(type_data("float", type_bin_data[6] / repeat_times * 1000, type_bin_data[7] / repeat_times * 1000, type_xml_data[6] / repeat_times * 1000, type_xml_data[7] / repeat_times * 1000))
    type_item.append(type_data("double", type_bin_data[8] / repeat_times * 1000, type_bin_data[9] / repeat_times * 1000, type_xml_data[8] / repeat_times * 1000, type_xml_data[9] / repeat_times * 1000))
    type_item.append(type_data("string", type_bin_data[10] / repeat_times * 1000, type_bin_data[11] / repeat_times * 1000, type_xml_data[10] / repeat_times * 1000, type_xml_data[11] / repeat_times * 1000))
    type_item.append(type_data("vector\n<double>", type_bin_data[12] / repeat_times * 1000, type_bin_data[13] / repeat_times * 1000, type_xml_data[12] / repeat_times * 1000, type_xml_data[13] / repeat_times * 1000))
    type_item.append(type_data("list\n<double>", type_bin_data[14] / repeat_times * 1000, type_bin_data[15] / repeat_times * 1000, type_xml_data[14] / repeat_times * 1000, type_xml_data[15] / repeat_times * 1000))
    type_item.append(type_data("set\n<double>", type_bin_data[16] / repeat_times * 1000, type_bin_data[17] / repeat_times * 1000, type_xml_data[16] / repeat_times * 1000, type_xml_data[17] / repeat_times * 1000))
    type_item.append(type_data("map\n<float, float>", type_bin_data[18] / repeat_times * 1000, type_bin_data[19] / repeat_times * 1000, type_xml_data[18] / repeat_times * 1000, type_xml_data[19] / repeat_times * 1000))
    plt.figure(figsize=(24, 12))
    plt.subplot(2, 2, 1)
    plt.title("Serialize Bin")
    plt.ylabel("Time (ms)")
    plt.xlabel("Type")
    plt.bar([item.name for item in type_item], [item.bin_serialize for item in type_item])
    plt.subplot(2, 2, 2)
    plt.title("Deserialize Bin")
    plt.ylabel("Time (ms)")
    plt.xlabel("Type")
    plt.bar([item.name for item in type_item], [item.bin_deserialize for item in type_item])
    plt.subplot(2, 2, 3)
    plt.title("Serialize XML")
    plt.ylabel("Time (ms)")
    plt.xlabel("Type")
    plt.bar([item.name for item in type_item], [item.xml_serialize for item in type_item])
    plt.subplot(2, 2, 4)
    plt.title("Deserialize XML")
    plt.ylabel("Time (ms)")
    plt.xlabel("Type")
    plt.bar([item.name for item in type_item], [item.xml_deserialize for item in type_item])
    plt.savefig("../record/type.png")
    
    
    size_bin_data = []
    size_xml_data = []
    line = bin_file.readline()
    while (line != "===\n"):
        size_bin_data.append(line.split(": ")[1])
        line = bin_file.readline()
    line = xml_file.readline()
    while (line != "===\n"):
        size_xml_data.append(line.split(": ")[1])
        line = xml_file.readline()
    size_item = []
    size_item.append(size_data("string", size_bin_data[0], size_xml_data[0]))
    size_item.append(size_data("vector\n<double>", size_bin_data[1], size_xml_data[1]))
    size_item.append(size_data("list\n<double>", size_bin_data[2], size_xml_data[2]))
    size_item.append(size_data("set\n<double>", size_bin_data[3], size_xml_data[3]))
    size_item.append(size_data("map\n<float, float>", size_bin_data[4], size_xml_data[4]))
    plt.figure(figsize=(24, 12))
    plt.subplot(2, 2, 1)
    plt.title("Serialize Bin")
    plt.ylabel("Time (ms)")
    plt.xlabel("Size (byte)")
    for item in size_item:
        plt.plot(item.size, item.bin_serialize, "-o", label=item.name, linewidth=0.5)
    plt.legend()
    plt.subplot(2, 2, 2)
    plt.title("Deserialize Bin")
    plt.ylabel("Time (ms)")
    plt.xlabel("Size (byte)")
    for item in size_item:
        plt.plot(item.size, item.bin_deserialize, "-o", label=item.name, linewidth=0.5)
    plt.legend()
    plt.subplot(2, 2, 3)
    plt.title("Serialize XML")
    plt.ylabel("Time (ms)")
    plt.xlabel("Size (byte)")
    for item in size_item:
        plt.plot(item.size, item.xml_serialize, "-o", label=item.name, linewidth=0.5)
    plt.legend()
    plt.subplot(2, 2, 4)
    plt.title("Deserialize XML")
    plt.ylabel("Time (ms)")
    plt.xlabel("Size (byte)")
    for item in size_item:
        plt.plot(item.size, item.xml_deserialize, "-o", label=item.name, linewidth=0.5)
    plt.legend()
    plt.savefig("../record/size.png")

    bin_file.close()
    xml_file.close()
    
    print("Done! Please check the record folder.")