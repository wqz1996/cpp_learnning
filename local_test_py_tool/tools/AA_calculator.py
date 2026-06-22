from datetime import datetime


def parse_time(time_str):
    """解析时间字符串"""
    return datetime.strptime(time_str, '%Y-%m-%d %H:%M')


def calculate_time_diff(start, end):
    """计算时间差（以分钟为单位）"""
    return (end - start).total_seconds() / 60


# 输入每个人的参与时间
participants = {
    "fan": {
        "start": "2024-01-01 19:00",
        "end": "2024-01-01 22:00"
    },
    "qize": {
        "start": "2024-01-01 18:30",
        "end": "2024-01-01 22:00"
    },
    "tongtong": {
        "start": "2024-01-01 21:00",
        "end": "2024-01-01 22:00"
    },
    "guangming": {
        "start": "2024-01-01 18:30",
        "end": "2024-01-01 22:00"
    }
}

# 输入总账单金额
total_bill = 296

# 计算每个人的参与时间
total_participation = 0
for name, times in participants.items():
    participants[name]['duration'] = calculate_time_diff(
        parse_time(times['start']), parse_time(times['end']))
    total_participation += participants[name]['duration']

# 根据参与时间比例分配账单
settlements = {}
for name, times in participants.items():
    share = (times['duration'] / total_participation) * total_bill
    settlements[name] = share

# 输出结果
for name, amount in settlements.items():
    print(f"{name} should pay: {amount:.2f}")
