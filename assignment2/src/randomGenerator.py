import random

def generate_random_str(randomlength=6):
  random_str =''
  base_str ='ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz0123456789'
  length =len(base_str) -1
  for i in range(randomlength):
    random_str +=base_str[random.randint(0, length)]
  return random_str

def generate_random_score(minNum=1, maxNum=5):
    return random.randint(minNum, maxNum);

if __name__ == "__main__":
    id_list = []
    for i in range(random.randint(5, 10)):
        id_list.append(generate_random_str())
    with open("../data/random_records.txt", mode='w') as f:
        for i in range(random.randint(10, 20)):
            write_str = generate_random_str()
            for i in range(len(id_list)):
                if (random.randint(0, 1) == 1):
                    write_str += "/{}:{}".format(id_list[i], generate_random_score())
            write_str += "\n"
            f.write(write_str)
        f.close()