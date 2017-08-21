#ifndef STYLE_STR
#define STYLE_STR "                                                             \
    QMainWindow {                                                               \
        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,           \
                                          stop: 0 #123, stop: 1 #357)           \
    }                                                                           \
                                                                                \
    QLabel {                                                                    \
        color: #def                                                             \
    }                                                                           \
                                                                                \
    QLineEdit {                                                                 \
        color: #eff;                                                            \
        background-color: rgba(255, 0, 127, 0.05);                              \
                                                                                \
        border-style: solid;                                                    \
        border-width: 1px;                                                      \
        border-color: #789                                                      \
    }                                                                           \
                                                                                \
    QPushButton {                                                               \
        color: #eff;                                                            \
        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,           \
                                          stop: 0 rgba(255, 255, 255, 0.15),    \
                                          stop: 1 rgba(0, 0, 0, 0.15));         \
                                                                                \
        border-style: solid;                                                    \
        border-width: 1px;                                                      \
        border-color: #789;                                                     \
                                                                                \
        padding: 2px                                                            \
    }                                                                           \
                                                                                \
    QPushButton:hover {                                                         \
        border-color: #abc                                                      \
    }                                                                           \
                                                                                \
    QPushButton:pressed {                                                       \
        border-color: #456;                                                     \
        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,           \
                                          stop: 0 rgba(0, 0, 0, 0.05),          \
                                          stop: 1 rgba(255, 255, 255, 0.05))    \
    }                                                                           \
                                                                                \
    QTextEdit {                                                                 \
        background-color: rgba(255, 255, 255, 0.9);                             \
                                                                                \
        border-style: none;                                                     \
        border-radius: 9px                                                      \
    }                                                                           \
                                                                                \
    QListWidget {                                                               \
        color: #eff;                                                            \
        background-color: rgba(255, 255, 255, 0.05);                            \
        border-style: solid;                                                    \
        border-width: 1px;                                                      \
        border-color: #789                                                      \
    }                                                                           \
"

#endif
