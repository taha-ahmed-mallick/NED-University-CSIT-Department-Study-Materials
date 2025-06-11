-- SELECT LAST_NAME, JOB_ID , HIRE_DATE FROM hr.employees
-- WHERE EXTRACT( YEAR FROM HIRE_DATE ) = 2013 ;

-- SELECT LAST_NAME, HIRE_DATE , 
-- TO_CHAR( NEXT_DAY( ADD_MONTHS( HIRE_DATE , 6 ) , 'Monday' ), 
-- 'DD FMMonth, YYYY' )
-- AS SALARY_REVIEW_DATE FROM hr.employees ;

--  -- Use number representation for order by. It orders from Sunday to Saturday.
-- SELECT LAST_NAME, HIRE_DATE, TO_CHAR(HIRE_DATE, 'DAY') AS DAY
-- FROM hr.employees
-- -- ORDER BY TO_CHAR( HIRE_DATE, 'D' ) ;
-- ORDER BY CASE TO_CHAR(HIRE_DATE, 'DY', 'NLS_DATE_LANGUAGE=ENGLISH')
--         WHEN 'MON' THEN 1
--         WHEN 'TUE' THEN 2
--         WHEN 'WED' THEN 3
--         WHEN 'THU' THEN 4
--         WHEN 'FRI' THEN 5
--         WHEN 'SAT' THEN 6
--         WHEN 'SUN' THEN 7
--     END;


-- -- HERE must cast both to same datatype OR will give error so use CASES.
-- SELECT LAST_NAME , NVL( TO_CHAR( SALARY + SALARY * COMMISSION_PCT ) ,
--  'No Commission') 
-- AS COMMISSION_AMOUNT FROM hr.employees ;

-- Can use CASES ALSO.
-- SELECT LAST_NAME, JOB_ID, DECODE(JOB_ID,
--         'AD_PRES', 'A',   'ST_MAN', 'B',
--         'IT_PROG', 'C',   'SA_REP', 'D',
--         'ST_CLERK', 'E',  '0') AS GRADE
-- FROM hr.employees;

-- SELECT e.LAST_NAME , e.DEPARTMENT_ID FROM hr.employees e
-- JOIN hr.employees m ON e.MANAGER_ID = m.EMPLOYEE_ID
-- WHERE e.DEPARTMENT_ID = m.DEPARTMENT_ID ;


-- SELECT LAST_NAME , HIRE_DATE FROM hr.employees 
-- WHERE HIRE_DATE > ( SELECT HIRE_DATE FROM hr.employees WHERE
--                     LOWER( LAST_NAME ) = 'davies' ) ;

-- SELECT COUNT(*) AS "Number of Managers" FROM hr.employees e
-- WHERE EXISTS (  SELECT 1 FROM hr.employees m
--                 WHERE m.MANAGER_ID = e.EMPLOYEE_ID );
-- SELECT COUNT(DISTINCT MANAGER_ID) AS "Number of Managers"
-- FROM hr.employees
-- WHERE MANAGER_ID IS NOT NULL;

-- SELECT COUNT(*) AS total_employees ,
-- SUM( CASE WHEN TO_CHAR( HIRE_DATE , 'YYYY' ) = '2015' THEN 1 END ) AS emps_2015 ,
-- COUNT( CASE WHEN EXTRACT( YEAR FROM HIRE_DATE ) = 2016 THEN 1 END ) AS emps_2016
-- FROM hr.employees ;


-- SELECT JOB_ID ,
--     SUM(CASE WHEN DEPARTMENT_ID = 20 THEN SALARY ELSE 0 END) AS dept_20_salary,
--     SUM(CASE WHEN DEPARTMENT_ID = 50 THEN SALARY ELSE 0 END) AS dept_50_salary,
--     SUM(CASE WHEN DEPARTMENT_ID = 80 THEN SALARY ELSE 0 END) AS dept_80_salary,
--     SUM(CASE WHEN DEPARTMENT_ID = 90 THEN SALARY ELSE 0 END) AS dept_90_salary,
--     SUM(CASE WHEN DEPARTMENT_ID IN (20, 50, 80, 90) THEN SALARY ELSE 0 END) AS total_salary
-- FROM hr.employees
-- WHERE DEPARTMENT_ID IN (20, 50, 80, 90)
-- GROUP BY JOB_ID
-- ORDER BY JOB_ID ; 


-- SELECT DEPARTMENT_ID, LAST_NAME, JOB_ID
-- FROM hr.employees 
-- WHERE DEPARTMENT_ID = ( SELECT DEPARTMENT_ID FROM hr.DEPARTMENTS  
--                         WHERE DEPARTMENT_NAME = 'Executive' ) ;


-- SELECT e.EMPLOYEE_ID , e.FIRST_NAME , e.LAST_NAME , 
-- e.SALARY , d.DEPARTMENT_NAME 
-- FROM hr.employees e 
-- JOIN hr.departments d ON e.department_id = d.DEPARTMENT_ID 
-- WHERE ( e.EMPLOYEE_ID , e.SALARY ) IN ( 
--     SELECT EMPLOYEE_ID , MAX( SALARY ) FROM hr.employees
--     GROUP BY EMPLOYEE_ID , DEPARTMENT_ID 
-- ) ;

-- SELECT constraint_name, constraint_type, table_name
-- FROM user_constraints;

-- ALTER TABLE ORDERS DISABLE CONSTRAINT order_pk ;

-- (e.g., TABLE, INDEX, VIEW).
-- SELECT object_name, object_type
-- FROM user_objects
-- WHERE object_name IN ('MY_STAFF', 'ORDER_FK') ; 

-- CREATE VIEW dept_sum_view AS
-- SELECT d.department_name AS name,MIN(e.salary) AS minsal,
--     MAX(e.salary) AS maxsal,AVG(e.salary) AS avgsal
-- FROM hr.employees e
-- JOIN hr.departments d ON e.department_id = d.department_id
-- GROUP BY d.department_name;

-- SELECT view_name, text
-- FROM user_views;

-- MORE CORRECT
-- SELECT e.first_name, e.last_name, d.department_name, e.salary
-- FROM hr.employees e
-- JOIN hr.departments d ON e.department_id = d.department_id
-- WHERE e.salary > ( SELECT AVG(e2.salary) FROM hr.employees e2
--                    WHERE e2.department_id = e.department_id )
-- ORDER BY d.department_name, e.salary DESC ;

-- -- Without Alias will give error for hire_date as-well.
-- SELECT e.EMPLOYEE_ID , ( e.FIRST_NAME || ' ' || e.LAST_NAME ) AS Emp_Full_Name,
-- j.JOB_TITLE, e.HIRE_DATE AS Emp_Hire_Date ,( m.FIRST_NAME || ' ' || m.LAST_NAME ) AS Manager_Full_Name,
-- m.HIRE_DATE AS Manager_Hire_Date
-- FROM hr.employees e 
-- JOIN hr.jobs j ON e.JOB_ID = j.JOB_ID 
-- JOIN hr.employees m ON e.MANAGER_ID = m.EMPLOYEE_ID 
-- WHERE e.HIRE_DATE > m.HIRE_DATE ;


-- SELECT d.DEPARTMENT_NAME, COUNT(*) AS emps_count , AVG( e.SALARY ) AS sal
-- FROM hr.employees e 
-- JOIN hr.departments d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID 
-- GROUP BY d.DEPARTMENT_NAME 
-- HAVING emps_count > 5 
-- ORDER BY sal DESC ;

-- -- 2_Methods
-- SELECT e.EMPLOYEE_ID , e.LAST_NAME , e.SALARY FROM hr.employees e
-- WHERE e.SALARY > ( SELECT AVG(SALARY) FROM hr.employees WHERE DEPARTMENT_ID = e.DEPARTMENT_ID ) ;

-- SELECT e.EMPLOYEE_ID,  e.LAST_NAME,  e.SALARY 
-- FROM hr.employees e
-- JOIN ( SELECT DEPARTMENT_ID, AVG(SALARY) AS avg_salary FROM hr.employees 
--         GROUP BY DEPARTMENT_ID) dept_avg
-- ON e.DEPARTMENT_ID = dept_avg.DEPARTMENT_ID
-- WHERE e.SALARY > dept_avg.avg_salary;


-- SELECT d.DEPARTMENT_NAME, AVG(e.SALARY) AS avg_dept_sal,
-- m.LAST_NAME AS manager_name, COUNT(*) AS emp_count
-- FROM hr.employees e
-- JOIN hr.departments d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID 
-- JOIN hr.employees m ON e.MANAGER_ID = m.EMPLOYEE_ID 
-- GROUP BY d.DEPARTMENT_NAME, m.LAST_NAME
-- HAVING AVG(e.SALARY) > (SELECT AVG(SALARY) FROM hr.employees)
-- ORDER BY avg_dept_sal DESC;


SELECT e.first_name || ' ' || e.last_name AS employee_name,
e.salary AS employee_salary, d.department_name,
m.first_name || ' ' || m.last_name AS manager_name, m.salary AS manager_salary,
COUNT(*) AS num_employees_above_avg
FROM hr.employees e
JOIN hr.departments d ON e.department_id = d.department_id
JOIN hr.employees m ON d.manager_id = m.employee_id
WHERE e.salary > ( SELECT AVG(salary) FROM hr.employees 
                   WHERE department_id = e.department_id )
GROUP BY e.first_name, e.last_name, e.salary, d.department_name, m.first_name, m.last_name, m.salary
ORDER BY d.department_name, num_employees_above_avg DESC;


