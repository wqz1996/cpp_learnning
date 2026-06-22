import random
import numpy as np


def compute_avg_1(data_list):
    count = 0.0
    avg = 0.0
    max_count = 100
    value = 0
    for i in range(len(data_list)):
        if count > max_count:
            avg = value
            count = 1
        else:
            avg = avg + (data_list[i] - avg) / count


def compute_avg_2(data_list):
    count = 0.0
    avg = 0.0
    for i in range(len(data_list)):
        count = count + 1
        # print("count: %d" % count)
        avg = avg + (float(data_list[i]) - avg) / float(count)
    return avg


def compute_avg_3(data_list):
    count = 0.0
    max_count = 5
    avg = 0.0
    pre_avg = 0.0
    sum = 0.0
    engage_flag = [1, 1, 1, 1, 1, 1, 1, 1, 0, 0]
    for i in range(len(data_list)):
        count = count + 1
        print("i = %d data = %.15f" % (i, data_list[i]))
        if count > max_count:
            avg = (avg + pre_avg) / (2.0 * max_count)
            pre_avg = avg
        else:
            sum = sum + data_list[i]
    return avg


if __name__ == '__main__':
    print("main function")
    test_list = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0]
    # test_list = []
    # for i in range(1, 1728000):
    #     rand_num = random.uniform(-0.1, 0.1)
    #     test_list.append(rand_num)
    #print(i)
    avg_1 = np.average(test_list)
    avg_2 = compute_avg_2(test_list)
    avg_3 = compute_avg_3(test_list)
    print("avg_1: %.15f avg_2 %.15f avg_3 %.15f" % (avg_1, avg_2, avg_3))
