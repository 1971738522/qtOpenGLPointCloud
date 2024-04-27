#include "03_appforms/frmmain.h"

int main(int argc, char *argv[])
{
    // --------------------------应用程序初始化
    QApplication a(argc, argv);
    // --------------------------UI初始化
    frmMain w;
    // --------------------------显示主窗口
    w.show();
    // --------------------------模态主窗口
    return a.exec();
}
