SELECT DISTINCT
    p2.name
FROM
    people p,
    people p2,
    movies m,
    stars s,
    stars s2
WHERE 1=1
    and p.id = s.person_id
    and m.id = s.movie_id
    and p.name = "Kevin Bacon" and p.birth = "1958"

    and p2.id = s2.person_id
    and s2.movie_id = s.movie_id
    and p.id <> p2.id
;
