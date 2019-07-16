# !/usr/lib/bin/python
# -*- coding utf-8 -*-

import os
import sys

def check_same_code(codes_list):
    size_of_list = len(codes_list)
    count = 0
    for i in range(size_of_list - 1):
        codes0 = codes_list[i]
        # end_idx = size_of_list
        near_num = 100
        end_idx = 0
        if i+1+near_num < size_of_list:
            end_idx = i+1+near_num
        else:
            end_idx = size_of_list
        for j in range(i+1, end_idx):
            for code in codes0:
                if len(codes0) > 1:
                    continue
                if code in codes_list[j]:
                    count += 1
                    print("%d %s, %s" % (count, codes0, codes_list[j]))


str1_qr_start = "'k5':'"
str2_qr_start = "'K5':'"
mulit_codes = []
bar_codes_array = []
with open(sys.argv[1], 'r') as f_data:
    line = f_data.readline()
    while line:
        str_start = "scan result is "
        str_end = ", send count"
        sn = line.find(str_start) + 15
        en = line.find(str_end)
        if sn != -1 and sn < en:
            bar_codes = []
            str_codes = line[sn:en]
            codes = str_codes.split('&')
            for code in codes:
                if "*" in code or code == "":
                    continue
                if "M" in code:
                    sn_bar = code.find(str1_qr_start) + 6
                    if sn_bar < 6:
                        sn_bar = code.find(str2_qr_start) + 6
                    if code[sn_bar:sn_bar+2] == "SF":
                        bar_codes.append(code[sn_bar:sn_bar + 15])
                    else:
                        bar_codes.append(code[sn_bar:sn_bar + 12])
                else:
                    bar_codes.append(code)

            bar_codes_set = list(set(bar_codes))
            bar_codes_array.append(bar_codes_set)
            num_code = 0
            if len(bar_codes_set) > 1:
                for i in range(len(bar_codes_set)):
                    if "2019" not in bar_codes_set[i]:
                        num_code += 1
                if num_code > 1:
                    print(bar_codes_set)
                    print(line)
                    mulit_codes.append(bar_codes_set)

        line = f_data.readline()

print("The number of codes is %d" % (len(bar_codes_array)))
print("The number of multi-codes is %d\n" %(len(mulit_codes)))
print("The same codes in different lines:\n")
check_same_code(bar_codes_array)


f_data.close()
