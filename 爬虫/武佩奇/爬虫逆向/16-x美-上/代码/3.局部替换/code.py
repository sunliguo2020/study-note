import subprocess
import re


def cmd(hex_arg):
    res = subprocess.check_output(f"node demo.js {hex_arg}", shell=True)
    res_string = res.decode("utf-8").strip()
    return res_string


def run():
    with open("f1.js", mode='r', encoding='utf-8') as fr, open("f2.js", mode='w', encoding='utf-8') as fw:
        for line in fr:
            match_list = re.findall("(_0x49a2b0\((.*?)\))", line)
            print(match_list)
            if not match_list:
                fw.write(line)
                continue
            for func_string, hex_str in match_list:
                line = line.replace(func_string, f'"{cmd(hex_str)}"')
            fw.write(line)


if __name__ == '__main__':
    run()
