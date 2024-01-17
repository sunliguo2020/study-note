# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
import random
import time


def get_slider_info():
    slider_list = []

    client_x = 300
    client_y = 500

    start_time = int(int(time.time() * 1000) % 1e5)

    width = random.randint(419, 431)

    for slice_distance in range(3, width, 26):
        if width - slice_distance <= 26:
            slice_distance = width
        start_time += random.randint(10, 1000)
        i = start_time
        o = f"{client_x + slice_distance}.00"
        u = f"{client_y + random.randint(-5, 5)}.00"
        a = f"{slice_distance}.00"
        f = f"{i};{o};{u};{a}"
        slider_list.append(f)
    return slider_list


def run():
    slider_list = get_slider_info()
    print(slider_list)


if __name__ == '__main__':
    run()