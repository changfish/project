import time
import pandas
from selenium import webdriver
from selenium.webdriver.support.ui import Select #use the Select
import pandas as pd
import os

#path && weburl
filepath = 'C:/Users/ChangYu/Desktop/coding/python/crawler/skill'
webpath = "C:/Users/ChangYu/Desktop/coding/python/driver/chromedriver"
url = "https://ent12.jctv.ntut.edu.tw/DispatchResultQry/CollegeQry.aspx"

#setting
options = webdriver.ChromeOptions()
options.add_argument('blink-settings=imagesEnabled=false')#不載入圖片
options.add_argument('--disable-dev-shm-usage')#使用共享內存RAM
options.add_argument('--disable-gpu')#規避部分chrome gpu bug
options.add_argument('--headless')

#start
driver = webdriver.Chrome(webpath, options=options)
driver.implicitly_wait(10)
driver.get(url)
time.sleep(2.5)
path = os.path.join(filepath,'skill.xlsx')  #setting the file path & file name
writer = pandas.ExcelWriter(path, engine='openpyxl')  #assign openpyxl engine

def trans_to_excel(selectname,page):
    #analyze table
    classtable = pd.read_html(page)
    if len(classtable)==2:
        df=classtable[1]
    else:
        df = classtable[0]

    #reset index
    df.reset_index(inplace=True, drop=True)

    #to csv && encoding
    df.to_excel(writer, sheet_name=selectname,encoding='utf_8_sig')  # 存到指定的sheet encoding=BOM-utf8

def ctrlweb(selectname):

    driver = webdriver.Chrome(webpath, options=options)
    driver.implicitly_wait(10)
    driver.get(url)
    time.sleep(2)

    #operator
    select = Select(driver.find_element_by_name('DropDownList1'))
    select.select_by_visible_text(selectname)

    # #click
    button = driver.find_element_by_id('Button1')
    button.click()
    time.sleep(1)
    trans_to_excel(selectname,driver.page_source)
    driver.quit()

college_op = []
tags = driver.find_element_by_name('DropDownList1')
tags = tags.find_elements_by_tag_name('option')

for tag in tags:
    college_op.append(tag.text)
driver.quit()
df = pd.DataFrame(college_op)
df.to_excel(writer, sheet_name="目錄",encoding='utf_8_sig')
for tag in college_op:
    ctrlweb(tag)

writer.save()
writer.close()
#finish
print("complete")
