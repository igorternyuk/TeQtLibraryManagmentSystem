USE library;
SELECT book.id AS ID, book.title AS Title, genre.name AS Genre, author.name AS Author, 
edition.name AS Edition, book.pages AS Pages, country.name AS Country, book.DOP AS DateOfPublication FROM book  
INNER JOIN genre, author, edition, country WHERE book.idGenre = genre.id AND 
book.idAuthor = author.id AND book.idEdition = edition.id AND edition.idCountry = country.id 
AND book.title LIKE '%Papel%' AND book.DOP > '2005-05-17' AND book.pages < 3000 
ORDER BY book.title DESC LIMIT 3;