#include <QApplication>
#include <QProcess>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>
#include <QDir>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFileInfoList>

void listExeFiles(const QString &dirPath, QStringList &exeFiles)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << dirPath;
        return;
    }

    // 设置过滤条件，只查找.exe文件
    dir.setNameFilters(QStringList() << "*.exe");
    dir.setFilter(QDir::Files); // 只考虑文件

    QFileInfoList fileInfoList = dir.entryInfoList();
    foreach (const QFileInfo &fileInfo, fileInfoList) {
        qDebug() << "Found EXE file:" << fileInfo.absoluteFilePath();
        exeFiles.append(fileInfo.absoluteFilePath());
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 获取屏幕分辨率
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Command Line Example");
    parser.addHelpOption();

        // 添加 --path 选项
    QCommandLineOption pathOption(QStringList() << "path" << "p",
                                  "Set the path.", "path");

    parser.addOption(pathOption);

    parser.process(app);

    // 获取 --path 的值
    QString path = parser.value(pathOption);
    if (!path.isEmpty()) {
        qDebug() << "Path specified with --path:" << path;
        // 在这里可以添加更多处理逻辑，比如调用函数处理路径
    } else {
        qDebug() << "No path specified";
    }

    QStringList exeFiles;
    listExeFiles(path, exeFiles);

    int numProcesses = exeFiles.length();
    int columns = static_cast<int>(sqrt(numProcesses));
    int rows = (numProcesses + columns - 1) / columns;

    int processWidth = screenWidth / columns;
    int processHeight = screenHeight / rows;

    for (int i = 0; i < numProcesses; ++i) {
        int x = (i % columns) * processWidth;
        int y = (i / columns) * processHeight;

        // 创建并启动子进程
        QProcess *process = new QProcess(&app);

        // 设置子进程程序的路径
        QString program = exeFiles.at(i); // 请替换为实际子进程程序路径

        // 设置子进程的参数
        QStringList arguments;
        arguments << "--width" << QString::number(processWidth)
                  << "--height" << QString::number(processHeight)
                  << "--x" << QString::number(x)
                  << "--y" << QString::number(y);

        // 启动子进程
        process->start(program, arguments);

        // 检查是否成功启动子进程
        if (!process->waitForStarted()) {
            qDebug() << "Failed to start process";
        } else {
            qDebug() << "Process started with arguments:" << program << " " << arguments;
        }
    }

    return app.exec();
}