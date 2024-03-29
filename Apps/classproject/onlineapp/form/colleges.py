from onlineapp.models import *
from django import forms

class AddCollege(forms.ModelForm):
	class Meta:
		model = College
		exclude = ['id']
		widgets = {
			'name':forms.TextInput(attrs={'class':'input','placeholder':'Enter college name'}),
            'acronym': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter acronym'}),
            'location': forms.TextInput(attrs={'class': 'input', 'placeholder': 'Enter location'}),
            'contact': forms.EmailInput(attrs={'class': 'input', 'placeholder': 'Enter contact'}),
        }