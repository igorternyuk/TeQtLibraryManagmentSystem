CREATE DATABASE library;
USE library;

CREATE TABLE country (
	id INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
    name TEXT
);

CREATE TABLE author (
	id INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
    name TEXT
);

CREATE TABLE edition (
	id INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
    name TEXT,
    idCountry INTEGER,
    FOREIGN KEY (idCountry) REFERENCES country(id)
);

CREATE TABLE genre (
	id INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
    name TEXT
);

CREATE TABLE book (
	id INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,
    title TEXT,
    pages INTEGER,
    DOP DATE,
    idGenre INTEGER,
    idAthor INTEGER,
    idEdition INTEGER,
    price DOUBLE,
    available INTEGER,
    FOREIGN KEY (idGenre) REFERENCES genre(id),
    FOREIGN KEY (idAthor) REFERENCES author(id),
	FOREIGN KEY (idEdition) REFERENCES edition(id)
);
