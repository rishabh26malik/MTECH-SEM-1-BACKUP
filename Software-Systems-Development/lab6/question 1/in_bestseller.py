import requests
from bs4 import BeautifulSoup
import csv

lim=2
addr="https://www.amazon.in"
DATA=[]
row=[]
DATA.append(["Name", "URL", "Author", "Price", "Number of Ratings", "Average Ratings"])
pgLink="https://www.amazon.in/gp/bestsellers/books/ref=zg_bs_pg_2?ie=UTF8&pg="

for i in range(1,3):
	#nextPg="https://link.springer.com/search/page/"
	#nextPg2='?date-facet-mode=between&facet-start-year=2010&facet-end-year=2015&query=text+AND+analytics+AND+"machine+learning"+AND+%28learn+OR+analyze+OR+extract%29+AND+NOT+%28search%29&showAll=true'
	#pageLink="https://www.amazon.in/gp/bestsellers/books/"
	pageLink=pgLink+str(i)
	page = requests.get(pageLink)
	soup = BeautifulSoup(page.content, 'html.parser')
	body=soup.find('body')
	#print(body)
	a_container=soup.find('div', class_='a-container')
	#print(a_container)
	a_fixed_left_flipped_grid=a_container.find('div', class_='a-fixed-left-flipped-grid')
	#print(a_fixed_left_flipped_grid)
	a_fixed_left_grid_inner=a_fixed_left_flipped_grid.find('div', class_='a-fixed-left-grid-inner')
	#print(a_fixed_left_grid_inner)
	a_fixed_left_grid_col_a_col_right=a_fixed_left_grid_inner.find('div', class_='a-fixed-left-grid-col a-col-right')
	#print(a_fixed_left_grid_col_a_col_right)
	zg_center_div=a_fixed_left_grid_col_a_col_right.find('div', id='zg-center-div')
	#print(zg_center_div)
	ol=zg_center_div.find('ol', class_='a-ordered-list a-vertical')
	#print(ol)
	LI=ol.find_all('li',class_="zg-item-immersion")
	for li in LI:
		span=li.find('span',class_="a-list-item")
		a_section=span.find('div',class_="a-section a-spacing-none aok-relative")
		aok=a_section.find('span',class_="aok-inline-block zg-item")
		a_link_normal=aok.find('a',class_="a-link-normal")

		#LINK
		link=addr+a_link_normal['href']
		#print(link)
		bookLink=link
		#row.append(link)

		book=li.find('div',class_="p13n-sc-truncate p13n-sc-line-clamp-1 p13n-sc-truncate-desktop-type2")
		bookname = book.get_text()
		row.append(bookname.strip())
		
		#STARS
		a_icon_row=li.find('div',class_="a-icon-row a-spacing-none")
		tmp=a_icon_row.find('a',class_="a-link-normal")
		i_tag=tmp.find('i')
		stars=i_tag.find('span')
		if(stars != None):
			Stars=stars.get_text()
			#row.append(stars.get_text())
		else:
			Stars="Not available"
			#row.append('---')
		
		#RATINGS
		Rating_tag=a_icon_row.find('a',class_="a-size-small a-link-normal")
		#print(Rating.get_text())
		if(Rating_tag != None):
			Ratings=Rating_tag.get_text()
		else:
			Ratings="Not available"
		#row.append(Rating.get_text())
		
		#AUTHOR
		a_row_a_size_small=aok.find('div',class_="a-row a-size-small")
		#print(a_row_a_size_small)
		a_tag=a_row_a_size_small.find('a', class_="a-size-small a-link-child")
		if(a_tag != None):
			author=a_tag.get_text()
			#print(author)
			#row.append(author)
		else:
			author="Not available"
			#row.append('---')

		#PRICE
		a_row=aok.find_all('div',class_="a-row")

		#print("------------")
		
		#print(a_row[len(a_row)-1].prettify())
		#exit()
		a_tag=a_row[len(a_row)-1].find('a',class_="a-link-normal a-text-normal")
		if(a_tag != None):
			price=a_tag.find('span').get_text()
			#row.append(price.strip())
		else:
			price="Not available"
			#row.append('---')
		#print(price.strip())
		row.append(bookLink)
		row.append(author)
		row.append(price)
		row.append(Ratings)
		row.append(Stars)
		DATA.append(row)
		row=[]
	#print(bookname)
#print(DATA[0])
#print(len(DATA))
#for i in DATA:
#	print(i)

with open('in_book.csv', 'w', newline='') as file:
    writer = csv.writer(file, quoting=csv.QUOTE_NONNUMERIC, delimiter=';')
    writer.writerows(DATA)