from onlineapp.models import *
from django import forms

class Student_Form(forms.ModelForm):
    class Meta:
        model = Student
        exclude = ['dob','id','college']
        widgets = {
            'name': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter student name'}),
            'email': forms.EmailInput(attrs={'class': 'input', 'placeholder': 'Enter email'}),
            'db_folder': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter database folder'}),
            'dropped_out': forms.CheckboxInput(attrs={'class':'input'}),
        }

class Mock_Form(forms.ModelForm):
    class Meta:
        model = MockTest1
        exclude = ['id','total','student']
        widgets = {
            'problem1': forms.NumberInput(attrs={'class': 'input', 'placeholder':'Enter problem1 marks'}),
            'problem2': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter problem2 marks'}),
            'problem3': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter problem3 marks'}),
            'problem4': forms.NumberInput(attrs={'class': 'input', 'placeholder': 'Enter problem4 marks'}),
        }