import openpyxl

import os
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'classproject.settings')
import django
django.setup()
from onlineapp.models import *
from django.db.models import Count

def getdata():
    c = College.objects.all()
    for i in c:
        print(i.name,i.location,i.acronym,i.contact)
    #print(c)

def getCountColleges():
    c = College.objects.count()
    print(c)

def getCntLocColl():
    c = College.objects.filter(location = "vizag")
    print(len(c))
    #for i in c:
     #   print(i)
def orderClgAsc():
    c = College.objects.order_by('acronym')
    for i in c:
        print(i.acronym)
def orderClgDes():
    c = College.objects.order_by('-acronym')[:5]
    for i in c:
        print(i.acronym)
def orderClgDesBottom():
    c = College.objects.order_by('-acronym')
    d = c[len(c)-5:]
    #print(d)
    for i in d:
        print(i.acronym)

def locNoClg():
    c = College.objects.values('location').distinct()
    #College.objects.group_by(id=1).annotate(count=Count('acronym').order_by('-count')
    #print(c)
    for i in c:
        loc = i['location']
        d = College.objects.filter(location=loc)
        print(loc,len(d))
    #print(c)
def locationsClg():
    c = College.objects.all()
    print(c.values('location').annotate(clgcnt=Count('location')))

def clgdropout():
    c = Student.objects.filter(dropped_out=True).values(College).distinct()
    print(c)

def clgNoStu():
    c = Student.objects.values('college__acronym').annotate(Count('college__name'))
    print(c)

def locStuOrd():
    c = Student.objects.values('college__location').annotate(count=Count('college__name')).order_by('-count')
    print(c)

def stugt30():
    c = Student.objects.values('name','college__name','mocktest1__total').filter(mocktest1__total__gt=30)
    for i in c:
        print(i)
    print(len(c))
def stugt30cnt():
    c = MockTest1.objects.filter(total__gt =30).count()
    print(c)

stugt30cnt()
#locStuOrd()
# clgNoStu()
#clgdropout()
#locationsClg()
#locNoClg()
#orderClgAsc()
#orderClgDes()
#orderClgDesBottom()
#getdata()
#getCountColleges()
#getCntLocColl()