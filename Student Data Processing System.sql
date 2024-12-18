
CREATE TABLE university (
    university_id INT PRIMARY KEY,
    name VARCHAR(100),
    address TEXT,
    email VARCHAR(100),
    city VARCHAR(100),
    university_type VARCHAR(20),
    year_of_foundation INT
);

CREATE TABLE faculty (
    faculty_id INT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    university_id INT,
    FOREIGN KEY (university_id) REFERENCES university(university_id)
);

CREATE TABLE department (
    department_id INT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    language VARCHAR(20),
    education_type VARCHAR(20),
    quota INT,
    top_quota INT,
    education_period INT,
    min_score_2024 FLOAT,
    min_order_2024 INT,
    faculty_id INT,
    FOREIGN KEY (faculty_id) REFERENCES faculty(faculty_id)
);

CREATE TABLE student (
    student_id INT PRIMARY KEY,
    name VARCHAR(100),
    surname VARCHAR(100),
    exam_score FLOAT,
    ranking INT,
    top_ranked BOOLEAN,
    preference1 INT,
    preference2 INT,
    preference3 INT,
    FOREIGN KEY (preference1) REFERENCES department(department_id),
    FOREIGN KEY (preference2) REFERENCES department(department_id),
    FOREIGN KEY (preference3) REFERENCES department(department_id)
);


INSERT INTO University (university_id, name, address, email, city, university_type, year_of_foundation)
VALUES 
(1, 'Ankara University', 'Ulus', 'info@au.edu', 'Ankara', 'state', 1988),
(2, 'Izmir Technical University', 'Karaburun', 'info@itu.edu', 'İzmir', 'state', 2020),
(3, 'Dokuz Eylul University', 'Buca', 'info@deu.edu', 'İzmir', 'state', 1990),
(4, 'Bilkent University', 'Keçiören', 'info@bilkent.edu', 'Ankara', 'private', 2010),
(5, 'Izmir University', 'Balçova', 'info@iu.edu', 'İzmir', 'private', 2015);

INSERT INTO Faculty (faculty_id, name, email, university_id)
VALUES
(31, 'Engineering Faculty', 'info@eng.uni.edu', 3),
(41, 'Engineering Faculty', 'info@eng.uni.edu', 4),
(51, 'Engineering Faculty', 'info@eng.uni.edu', 5),
(22, 'Medicine Faculty', 'info@med.uni.edu', 2),
(32, 'Medicine Faculty', 'info@med.uni.edu', 3),
(42, 'Medicine Faculty', 'info@med.uni.edu', 4),
(52, 'Medicine Faculty', 'info@med.uni.edu', 5),
(13, 'Law Faculty', 'info@law.uni.edu', 1),
(33, 'Law Faculty', 'info@law.uni.edu', 3),
(24, 'Science Faculty', 'info@scinc.uni.edu', 2),
(34, 'Science Faculty', 'info@scinc.uni.edu', 3),
(25, 'Literature Faculty', 'info@ltrtr.uni.edu', 2),
(45, 'Literature Faculty', 'info@ltrtr.uni.edu', 4),
(55, 'Literature Faculty', 'info@ltrtr.uni.edu', 5),
(36, 'Education Faculty', 'info@edctn.uni.edu', 3),
(46, 'Education Faculty', 'info@edctn.uni.edu', 4),
(56, 'Education Faculty', 'info@edctn.uni.edu', 5);

INSERT INTO Department (department_id, name, email, language, education_type, quota, top_quota, education_period, min_score_2024, min_order_2024, faculty_id)
VALUES
(311, 'Computer Engineering', 'info@ce.uni.edu', 'English', 'ee', 40, 2, 4, 125000, 1120, 31),
(411, 'Computer Engineering', 'info@ce.uni.edu', 'Turkish', 'fe', 55, 2, 4, 100000, 1120, 41),
(511, 'Computer Engineering', 'info@ce.uni.edu', 'English', 'ee', 60, 3, 4, 110000, 1120, 51),
(312, 'Space Engineering', 'info@spc.uni.edu', 'English', 'ee', 45, 8, 4, 115000, 1250, 31),
(412, 'Space Engineering', 'info@spc.uni.edu', 'Turkish', 'ee', 50, 9, 4, 95000, 1250, 41),
(313, 'Electrical Engineering', 'info@elc.edu', 'English', 'ee', 45, 7, 4, 95000, 4000, 31),
(513, 'Electrical Engineering', 'info@wlc.edu', 'Turkish', 'fe', 60, 6, 4, 80000, 4000, 51),
(314, 'Machine Engineering', 'info@mch.edu', 'English', 'ee', 50, 5, 4, 80000, 4000, 31),
(315, 'Geology Engineering', 'info@law.edu', 'English', 'ee', 55, 4, 4, 75000, 4000, 31),
(415, 'Geology Engineering', 'info@law.edu', 'Turkish', 'fe', 60, 6, 4, 70000, 4000, 41),
(515, 'Geology Engineering', 'info@law.edu', 'Turkish', 'fe', 70, 8, 4, 65000, 4000, 51),
(221, 'Neurology Department', 'info@neu.uni.edu', 'English', 'fe', 55, 3, 6, 120000, 1010, 22),
(321, 'Neurology Department', 'info@neu.uni.edu', 'English', 'ee', 30, 4, 6, 110000, 1010, 32),
(421, 'Neurology Department', 'info@neu.uni.edu', 'Turkish', 'ee', 50, 3, 6, 115000, 1010, 42),
(521, 'Neurology Department', 'info@neu.uni.edu', 'Turkish', 'ee', 60, 5, 6, 110000, 1010, 52),
(322, 'Dental Department', 'info@den.uni.edu', 'Turkish', 'ee', 45, 5, 5, 115000, 1010, 32),
(422, 'Dental Department', 'info@den.uni.edu', 'Turkish', 'ee', 55, 4, 5, 100000, 1010, 42),
(131, 'Law Department', 'info@law.uni.edu', 'Turkish', 'ee', 70, 3, 4, 90000, 1010, 13),
(331, 'Law Department', 'info@law.uni.edu', 'Turkish', 'ee', 75, 3, 4, 95000, 1010, 33),
(241, 'Physics Department', 'info@phy.uni.edu', 'Turkish', 'ee', 70, 4, 3, 75000, 1010, 24),
(341, 'Physics Department', 'info@phy.uni.edu', 'Turkish', 'ee', 80, 5, 3, 70000, 1010, 34),
(242, 'Chemistry Department', 'info@cms.uni.edu', 'Turkish', 'ee', 80, 5, 3, 65000, 1010, 24),
(342, 'Chemistry Department', 'info@cms.uni.edu', 'Turkish', 'ee', 75, 5, 3, 60000, 1010, 34),
(343, 'Mathematics Department', 'info@mat.uni.edu', 'Turkish', 'ee', 90, 4, 3, 75000, 1010, 34),
(344, 'Biology Department', 'info@bio.uni.edu', 'Turkish', 'ee', 85, 5, 3, 70000, 1010, 34),
(251, 'History Department', 'info@his.uni.edu', 'Turkish', 'ee', 75, 4, 2, 55000, 1010, 25),
(551, 'History Department', 'info@his.uni.edu', 'Turkish', 'ee', 70, 4, 2, 50000, 1010, 55),
(252, 'Philosophy Department', 'info@plsp.uni.edu', 'Turkish', 'ee', 80, 5, 2, 55000, 1010, 25),
(452, 'Philosophy Department', 'info@plsp.uni.edu', 'Turkish', 'fe', 85, 4, 2, 45000, 1010, 45),
(552, 'Philosophy Department', 'info@plsp.uni.edu', 'Turkish', 'ee', 75, 6, 2, 40000, 1010, 55),
(453, 'Psychology Department', 'info@phy.uni.edu', 'Turkish', 'ee', 85, 6, 2, 45000, 1010, 45),
(553, 'Psychology Department', 'info@phy.uni.edu', 'Turkish', 'ee', 85, 5, 2, 40000, 1010, 55),
(361, 'Teaching Department', 'info@tch.uni.edu', 'Turkish', 'ee', 65, 4, 3, 70000, 1010, 36),
(461, 'Teaching Department', 'info@tch.uni.edu', 'Turkish', 'ee', 60, 4, 3, 55000, 1010, 46),
(561, 'Teaching Department', 'info@tch.uni.edu', 'Turkish', 'ee', 70, 5, 3, 35000, 1010, 56);

INSERT INTO Student (student_id, name, surname, exam_score, ranking, top_ranked, preference1, preference2, preference3)
VALUES
(1000, 'Ayşe', 'Gaye', 150000, 1000, TRUE, 311, 411, 511),
(2000, 'Ali', 'Veli', 90000, 1200, FALSE, 521, 415, 342),
(3000, 'Fatma', 'Ayşe', 100000, 1100, TRUE, 411, 312, 313),
(4000, 'Veli', 'Ali', 80000, 1500, FALSE, 315, 513, 321),
(5000, 'Aylin', 'Ceylin', 120000, 1050, TRUE, 311, 251, 343),
(6000, 'Ahmet', 'Mehmet', 84000, 1400, FALSE, 453, 311, 561);

/*1) Find the university names which are located in the
cities whose name starts with “A” and founded after 1990.*/
SELECT name
FROM University
WHERE city LIKE 'A%' AND year_of_foundation > 1990;


/*2) Find the universities which include “Engineering” and
“Medicine” Faculties.*/
SELECT DISTINCT u.name
FROM University u
JOIN Faculty f ON u.university_id = f.university_id
WHERE f.name IN ('Engineering Faculty', 'Medicine Faculty');


/*3) Find the count of faculties according to university types.*/
SELECT u.university_type, COUNT(f.faculty_id) AS faculty_count
FROM University u
LEFT JOIN Faculty f ON u.university_id = f.university_id
GROUP BY u.university_type;


/*4) Find the departments that contain “engineering”
and are the type of “ee”.*/
SELECT *
FROM Department
WHERE name ILIKE '%engineering%' AND education_type = 'ee';


/*5) Find the top five departments with the longest
education period and the highest score.*/
-- ilk önce score sıralaması yapıldı
SELECT *
FROM Department
ORDER BY min_score_2024 DESC, education_period DESC
LIMIT 5;


/*6) Find the most preferred 4-year departments. 
departman ismi olcak*/
SELECT d.name AS department_name, u.name AS university_name, COUNT(*) AS preference_count
FROM (
    SELECT preference1 AS preference FROM Student
    UNION ALL
    SELECT preference2 AS preference FROM Student
    UNION ALL
    SELECT preference3 AS preference FROM Student
) AS preferences
INNER JOIN Department d ON preferences.preference = d.department_id
INNER JOIN Faculty f ON d.faculty_id = f.faculty_id
INNER JOIN University u ON f.university_id = u.university_id
WHERE d.education_period = 4
GROUP BY d.name, u.name
ORDER BY COUNT(*) DESC
LIMIT 5;




/*7) List the students who prefer the Department of
Computer Engineering as their first choice according
to their exam score in a descending order.*/
SELECT *
FROM Student
WHERE preference1 = (
    SELECT department_id 
    FROM Department 
    WHERE name = 'Computer Engineering'
    LIMIT 1
)
ORDER BY exam_score DESC;


/*8) Update the Faculty of Engineering in Dokuz Eylül University
to be located in Izmir Technical University.*/
-- Deu daki engineering fakültesinin university id si değiştirilir
UPDATE Faculty
SET university_id = (
        SELECT university_id
        FROM University
        WHERE name = 'Izmir Technical University'
    )
WHERE name = 'Engineering Faculty'
    AND university_id = (
        SELECT university_id
        FROM University
        WHERE name = 'Dokuz Eylul University'
    );


/*9) Extend the current education period of the departments
under the Faculty of Law by one year.*/
UPDATE Department
SET education_period = education_period + 1
WHERE faculty_id IN (
    SELECT faculty_id
    FROM Faculty
    WHERE name = 'Law Faculty'
);

/*10) Delete the faculties and departments in İzmir University.*/
-- İlgili student kayıtlarını güncelleme
UPDATE student
SET preference1 = NULL
WHERE preference1 IN (
    SELECT department_id
    FROM Department
    WHERE faculty_id IN (
        SELECT faculty_id
        FROM Faculty
        WHERE university_id = (
            SELECT university_id
            FROM University
            WHERE name = 'Izmir University'
        )
    )
);

UPDATE student
SET preference2 = NULL
WHERE preference2 IN (
    SELECT department_id
    FROM Department
    WHERE faculty_id IN (
        SELECT faculty_id
        FROM Faculty
        WHERE university_id = (
            SELECT university_id
            FROM University
            WHERE name = 'Izmir University'
        )
    )
);

UPDATE student
SET preference3 = NULL
WHERE preference3 IN (
    SELECT department_id
    FROM Department
    WHERE faculty_id IN (
        SELECT faculty_id
        FROM Faculty
        WHERE university_id = (
            SELECT university_id
            FROM University
            WHERE name = 'Izmir University'
        )
    )
);

-- İlgili department kayıtlarını silme
DELETE FROM Department
WHERE faculty_id IN (
    SELECT faculty_id
    FROM Faculty
    WHERE university_id = (
        SELECT university_id
        FROM University
        WHERE name = 'Izmir University'
    )
);

-- İlgili faculty kayıtlarını silme
DELETE FROM Faculty
WHERE university_id = (
    SELECT university_id
    FROM University
    WHERE name = 'Izmir University'
);
