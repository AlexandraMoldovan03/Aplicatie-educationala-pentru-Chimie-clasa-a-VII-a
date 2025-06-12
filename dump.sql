
-- Dump SQL pentru aplicația educațională de chimie

CREATE DATABASE IF NOT EXISTS chimie_db;
USE chimie_db;

CREATE TABLE users (
  id INT(11) NOT NULL AUTO_INCREMENT,
  username VARCHAR(50) NOT NULL,
  password VARCHAR(255) NOT NULL,
  email VARCHAR(255) NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY username (username)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE rezultate_teste (
  id INT(11) NOT NULL AUTO_INCREMENT,
  user VARCHAR(50) NOT NULL,
  nota INT(11) NOT NULL,
  data DATETIME NOT NULL,
  test VARCHAR(50) DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

CREATE TABLE sesiuni_invatare (
  id INT(11) NOT NULL AUTO_INCREMENT,
  username VARCHAR(50) DEFAULT NULL,
  start_time DATETIME DEFAULT NULL,
  end_time DATETIME DEFAULT NULL,
  durata_secunde INT(11) DEFAULT NULL,
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
