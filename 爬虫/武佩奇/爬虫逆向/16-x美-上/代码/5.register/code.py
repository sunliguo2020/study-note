import time
import json
import requests
import random
import datetime


def gen_captcha_uuid():
    total_string = "ABCDEFGHJKMNPQRSTWXYZabcdefhijkmnprstwxyz2345678"
    part = "".join([random.choice(total_string) for i in range(18)])
    ctime = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    captcha_uuid = f"{ctime}{part}"
    return captcha_uuid


def run():
    captcha_uuid = gen_captcha_uuid()

    res = requests.get(
        url="https://captcha1.fengkongcloud.cn/ca/v1/register",
        params={
            "captchaUuid": captcha_uuid,
            "model": "select",
            "appId": "default",
            "rversion": "1.0.4",
            "sdkver": "1.1.3",
            "callback": "sm_callback",
            "organization": "xQsKB7v2qSFLFxnvmjdO",
            "channel": "DEFAULT",
            "lang": "zh-cn",
            "data": "{}"
        }
    )

    print(res.text)
    data_dict = json.loads(res.text.strip("sm_callback").strip("(").strip(")"))
    print(data_dict)


if __name__ == '__main__':
    run()
