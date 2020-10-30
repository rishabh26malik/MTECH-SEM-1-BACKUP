# Q1

select fname, lname 
from EMPLOYEE 
where Super_ssn in (select ssn from EMPLOYEE 
		where fname = 'Jennifer' and lname = 'Wallace');


# Q2

select Fname 
from EMPLOYEE as emp, DEPENDENT as dep
where emp.ssn=dep.essn and emp.sex=dep.sex and emp.fname=dep.dependent_name; 


# Q3

select fname, lname
from EMPLOYEE emp, (select Essn 
		from WORKS_ON 
		where hours>5 
		and Pno in (select Pnumber from PROJECT 
			where Pname="ProductX" and Dnum=5)) tmp
where emp.ssn=tmp.essn and emp.dno=5;



# Q4

select pnumber, dnumber, lname, bdate, address, bdate 
from EMPLOYEE emp, (select DISTINCT Pnumber, Dname, Dnumber, mgr_ssn
		from DEPARTMENT dpt, (select Pnumber,Dnum
		from PROJECT where Plocation="Stafford") tmp
         where dpt.Dnumber=tmp.Dnum) tmp2         
where emp.ssn=tmp2.mgr_ssn


# Q5

select Fname
from EMPLOYEE emp,
(select Essn
from
(select Essn, count(pno) Cnt
from WORKS_ON
where Pno in (select Pnumber
		from PROJECT
		where Dnum=5)         
group by Essn ) t1
where t1.Cnt in ( select count(*)
		from PROJECT where Dnum=5 )) t2        
where t2.Essn=emp.Ssn
