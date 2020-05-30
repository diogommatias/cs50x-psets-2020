SELECT
    m.title
FROM
    movies m,
    stars s,
    people p,

    stars s2,
    people p2
WHERE 1=1
    and m.id = s.movie_id
    and p.id = s.person_id
    and p.name LIKE "Johnny Depp"

    and m.id = s2.movie_id
    and p2.id = s2.person_id
    and p2.name LIKE "Helena Bonham Carter"
;
