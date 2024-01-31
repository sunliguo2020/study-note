import subprocess

hex_arg = "0x13a"
res = subprocess.check_output(f"node demo.js {hex_arg}", shell=True)
res_string = res.decode("utf-8").strip()
print(res_string)

# 休息 21:30继续