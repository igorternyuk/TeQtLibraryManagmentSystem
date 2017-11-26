USE library;
SELECT book.id AS ID, book.title AS Title, genre.name AS Genre, author.name AS Author, 
edition.name AS Edition, book.pages AS Pages, country.name AS Country, book.DOP AS DateOfPublication FROM book  
INNER JOIN genre, author, edition, country WHERE book.idGenre = genre.id AND 
book.idAuthor = author.id AND book.idEdition = edition.id AND edition.idCountry = country.id 
AND book.title LIKE '%a%' 
 AND book.pages > 5  AND book.pages < 5000 
 AND book.price > 50 AND book.price < 5000 
 AND book.DOP > '2005-05-17'  AND book.DOP < '2017-05-17' 
 AND author.id = 1
 AND edition.id = 1
 AND genre.id = 1
 AND book.available > 0 
 ORDER BY book.title DESC;