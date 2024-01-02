-- database: d:\Users\31003\Desktop\vscode\C++\Minun\w\cache.db
-- 要运行整个文件，请按窗口右上角的▷按钮。
CREATE TABLE IF NOT EXISTS
    test1 (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        pid INTEGER not NULL UNIQUE,
        name char(20)
    );

CREATE TABLE IF NOT EXISTS
    test2 (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        pid INTEGER not NULL UNIQUE,
        name char(20)
    );

INSERT INTO
    test1 (pid, name)
VALUES
    (2, "h1"),
    (3, "h2");

INSERT INTO
    test1 (pid, name)
VALUES
    (4, "h2"),
    (5, "h2"),
    (6, "h1"),
    (7, "h2"),
    (8, "h1"),
    (9, "h2");

SELECT
    *
FROM
    test1
WHERE
    name = (
        SELECT
            name
        FROM
            test2
        WHERE 
        id =2
    );

