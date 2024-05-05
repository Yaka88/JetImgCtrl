//JetImgCtrlApi.h
//
// 文件名	: JetImgCtrlApi.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 控件API文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
//错误返回码部分：
/*
-1200:超过允许显示张数;
-1201:内存不够；
-1202:准备图象显示位图失败；
-1203:指定图象序号越界；
-1204:显示线条失败；
-1205:显示方框失败；
-1206:显示点失败；
-1207:显示字符串失败；
-1208:图象上的指定元素序号越界；
-1209:打开图象文件出错；
-1210:使某元素可见失败；
-1211:申请的内存长度不够.
-1299:还未支持此种功能；
*/
//绘图状态，如点、线条、区域、文本
#define POINT_SET 0
#define LINE_SET  1
#define RECT_SET  2
#define TEXT_SET  3

//文本框编辑类型
#define STATIC	 0
#define EDIT	 1
#define COMBOBOX 2
#define LISTBOX  3

//图象显示状态：
#define STRETCH_SCALE_FILLRECT		1	//图象按控件窗口大小显示，但是图象本身保证长宽比例；(缺省设置)
#define STRETCH_NOTSCALE_FILLRECT	2	//图象按控件窗口大小显示，不用保证长宽比例，充满整个区域；
#define STRETCH_NOT					3	//实际大小；
#define STRETCH_ANY_SCALE			4	//图象按任意比例显示，但是图象本身保证长宽比例；(缺省设置)

