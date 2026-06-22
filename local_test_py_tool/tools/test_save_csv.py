import pandas as pd
import csv
import os


def to_csv(title_list, data_list, output_folder):
    print("running csv function")
    output_file = 'test.csv'
    output_file = os.path.join(os.path.abspath(output_folder), output_file)
    print("Start saving as csv %s" % output_file)
    with open(output_file, 'w') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(title_list)
        csv_writer.writerow(data_list)
    print("Successfully saving as csv")


if __name__ == '__main__':
    output_folder = '/home/wu/local_test_py_tool/csv_file'
    title_list = ['vehicle_name', 'bag_link', 'grafana_link']
    data_list = [
        '20230423T145701_pdb-l4e-b0006_2.bag',
        'https://bagdb-cn.plus.ai/plusview?bagName=%20%2220230423T145701_pdb-l4e-b0006_2.bag%20%22&currentTime=1682235378000',
        'https://grafana-cn.plusai.co/d/2SoVcr1Vk/longitudinal-analysis?orgId=1&from=1682235352232.2532&to=1682236381208.5647&var-bag_name=20230423T145701_pdb-l4e-b0006_2.bag&var-vehicle=pdb-l4e-b0006&var-vehicle_name=pdb-l4e-b0006&theme=dark'
    ]

    to_csv(title_list, data_list, output_folder)
