-- Enable Foreign Key
PRAGMA foreign_keys = ON;

-- Create User table
CREATE TABLE IF NOT EXISTS user_tb (
    user_id INTEGER PRIMARY KEY ASC,
    name TEXT NOT NULL,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);

-- Create things table
CREATE TABLE IF NOT EXISTS things_tb (
    things_id INTEGER PRIMARY KEY,
    type TEXT CHECK(type IN ('NOTE', 'TODO', 'EVENT', 'SHOPPING')),
    date_created TEXT NOT NULL DEFAULT (DATE('NOW')),
    things_text TEXT NOT NULL,
    user_id INTEGER,
    FOREIGN KEY(user_id) REFERENCES user_tb(user_id)
);

-- Create event data table
CREATE TABLE IF NOT EXISTS event_data_tb (
    things_id INTEGER PRIMARY KEY,
    date_of_event TEXT,
    FOREIGN KEY(things_id) REFERENCES things_tb(things_id)
);

-- Create todo data table
CREATE TABLE IF NOT EXISTS todo_data_tb (
    things_id INTEGER PRIMARY KEY,
    status TEXT CHECK(status IN ('Listed', 'Done', 'Canceled')) NOT NULL DEFAULT ('Listed'),
    deadline TEXT,
    FOREIGN KEY(things_id) REFERENCES things_tb(things_id)
);

-- Create shopping data table
CREATE TABLE IF NOT EXISTS shopping_data_tb (
    things_id INTEGER PRIMARY KEY,
    status TEXT CHECK(status IN ('Listed', 'Done', 'Canceled')) NOT NULL DEFAULT ('Listed'),
    quantity INTEGER,
    price_per_pcs INTEGER,
    FOREIGN KEY(things_id) REFERENCES things_tb(things_id)
);

-- The password is Master123.
INSERT INTO user_tb (name, username, password) VALUES ('masterName', 'master', '$2a$10$Ye5FNyuXpMMc0MGI.mRTKO55GhvSQCZTDofrXNwOqgpkYGgLKu1mC');
-- END