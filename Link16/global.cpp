#include "global.h"

std::map<std::string, std::string> g_JType = {
	{"0 0", "初始入网"},	{"0 1", "测试"},			{"0 2", "网络时间更新"},
	{"0 3" , "时隙分配"},	{"0 4", "无线电中继控制"},	{"0 5", "二次传播中继"},
	{"0 6", "通信控制"},	{"0 7", "时隙再分配"},		{"1 0", "连通询问"},
	{"1 1", "连通状态"},	{"1 2", "路径建立"},		{"1 3", "确认"},
	{"3 2", "空中航迹"},	{"12 2", "飞机的准确方位"},	{"31 1", "空中更换密钥"},
	{"31 7", "无信息"}
};