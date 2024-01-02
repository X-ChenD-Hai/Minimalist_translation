-- database: d:\Users\31003\Desktop\vscode\C++\Minun\bin\cache\transdata.db

-- 要运行整个文件，请按窗口右上角的▷按钮。

SELECT * FROM "tbl_reply"
ORDER BY "to_id" DESC;

INSERT INTO tbl_text (hash,text) VALUES(?,?);


CREATE TABLE IF NOT EXISTS
    tbl_engine (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        label char(30) NOT NULL UNIQUE
    );

CREATE TABLE IF NOT EXISTS
    "tbl_text" (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        hash TEXT NOT NULL,
        text TEXT NOT NULL UNIQUE,
        timestat INTEGER NOT NULL
    );

CREATE TABLE IF NOT EXISTS
    tbl_reply (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        engine_id INT NOT NULL,
        from_text_id INT NOT NULL,
        to_text_id INT,
        from_id INT NOT NULL,
        to_id INT NOT NULL,
        timestat INT NOT NULL,
        count INT NOT NULL
    );

INSERT INTO
    tbl_engine (label)
VALUES
    (?);

INSERT INTO
    tbl_engine (label)
VALUES
    ("Hello");

INSERT INTO
    tbl_engine (label)
VALUES
    ("Hello");

DELETE FROM tbl_engine
WHERE
    label = "Hello";

SELECT
    *
FROM
    tbl_engine;

SELECT
    label
FROM
    tbl_engine;

DELETE FROM tbl_engine;

INSERT INTO
    tbl_engine (label)
VALUES
    ("1"),
    ("2");


INSERT INTO tbl_reply (engine_id,from_hash_id,from_id,to_id,timestat,count) VALUES (?,?,?,?,?,?);
DELETE FROM tbl_text WHERE id = ?;
SELECT *FROM tbl_text WHERE id = (SELECT to_id FROM tbl_reply WHERE from_hash_id=?);

SELECT id FROM tbl_text WHERE hash=?;