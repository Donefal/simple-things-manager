-- Enable foreign key support
PRAGMA foreign_keys = ON;

-- Insert sample users
-- password123, securepass, test123
INSERT INTO user_tb (name, username, password) VALUES 
('John Doe', 'johndoe', '$2a$10$6FvdNuv.tmLMw0EEUNFG1uDXYojOjgjGQ/.IOKRf.ue65QZ2DCwuS'),
('Jane Smith', 'janesmith', '$2a$10$YlbaBWbZvbqkAVf6w7jrsun4jtZZivvMkTP8uIXa3mAiKbwsB/PlG'),
('Bob Johnson', 'bjohnson', '$2a$10$hHEH.ICN.L.8NMAfaIDTTObgCKkn66BdJ6Pz5AQbl07ioJxs.CX22');

-- Insert sample notes
INSERT INTO things_tb (type, things_text, user_id) VALUES
('NOTE', 'Meeting with team about project updates', 2),
('NOTE', 'Ideas for the new marketing campaign', 3),
('NOTE', 'Grocery list for the week', 4);

-- Insert sample todos
INSERT INTO things_tb (type, things_text, user_id) VALUES
('TODO', 'Finish project documentation', 2),
('TODO', 'Call client for feedback', 3),
('TODO', 'Clean the garage', 4);

-- Insert corresponding todo data
INSERT INTO todo_data_tb (things_id, status, deadline) VALUES
(4, 'Listed', '2023-12-15'),
(5, 'Listed', '2023-12-10'),
(6, 'Done', '2023-12-05');

-- Insert sample events
INSERT INTO things_tb (type, things_text, user_id) VALUES
('EVENT', 'Team building activity', 2),
('EVENT', 'Dentist appointment', 3),
('EVENT', 'Family dinner', 4);

-- Insert corresponding event data
INSERT INTO event_data_tb (things_id, date_of_event) VALUES
(7, '2023-12-20'),
(8, '2023-12-12 14:30'),
(9, '2023-12-24 18:00');

-- Insert sample shopping items
INSERT INTO things_tb (type, things_text, user_id) VALUES
('SHOPPING', 'Milk', 2),
('SHOPPING', 'Bread', 3),
('SHOPPING', 'Eggs', 4);

-- Insert corresponding shopping data
INSERT INTO shopping_data_tb (things_id, status, quantity, price_per_pcs) VALUES
(10, 'Listed', 2, 350),  
(11, 'Done', 1, 250),     
(12, 'Listed', 12, 150); 

-- User with no items
INSERT INTO user_tb (name, username, password) VALUES 
('Empty User', 'emptyuser', 'noposts');

-- Completed todo
INSERT INTO things_tb (type, things_text, user_id) VALUES
('TODO', 'Already done task', 2);
INSERT INTO todo_data_tb (things_id, status, deadline) VALUES
(13, 'Done', '2023-11-30');

-- Canceled shopping item
INSERT INTO things_tb (type, things_text, user_id) VALUES
('SHOPPING', 'Canceled item', 3);
INSERT INTO shopping_data_tb (things_id, status, quantity, price_per_pcs) VALUES
(14, 'Canceled', 1, 1000);

-- Event in the past
INSERT INTO things_tb (type, things_text, user_id) VALUES
('EVENT', 'Past event', 4);
INSERT INTO event_data_tb (things_id, date_of_event) VALUES
(15, '2023-11-01');

-- END