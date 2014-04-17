
CREATE USER 'inventaari'@'%' IDENTIFIED BY PASSWORD '*0EE04DF57962256876CDC0A4494A526634E023E9';

CREATE DATABASE inventaari
	DEFAULT CHARACTER SET utf8
	DEFAULT COLLATE utf8_general_ci;

USE inventaari;

CREATE TABLE products
(  code CHAR(12) NOT NULL 
,	name VARCHAR(200) NOT NULL
,	price NUMERIC(22,2) NOT NULL
,	stock INTEGER NOT NULL
,	CONSTRAINT products_pkey PRIMARY KEY (code)
,	CONSTRAINT products_name UNIQUE products_name_key (name)
);

GRANT SELECT, INSERT, UPDATE, DELETE ON products TO 'inventaari'@'%';

