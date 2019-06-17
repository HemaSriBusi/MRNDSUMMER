from rest_framework import serializers
from .models import *

class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model = College
        fields = ('id','name','location','acronym','contact')

class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Student
        fields = ('id','name','dob','email','db_folder','dropped_out','college')

class MockTest1Serializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('problem1','problem2','problem3','problem4','total')

class StudentDetailsSerializer(serializers.ModelSerializer):
    mocktest1 = MockTest1Serializer(read_only=False, many=False)

    class Meta:
        model = Student
        fields = ('id', 'name', 'dob', 'email', 'db_folder', 'dropped_out', 'college','mocktest1')

    def create(self, validated_data):
        mock_data = validated_data.pop('mocktest1')
        student = Student.objects.create(**validated_data)
        MockTest1.objects.create(student=student, **mock_data)
        return student

    def update(self, instance, validated_data):
        instance.name = validated_data.get("name", instance.name)
        instance.dob = validated_data.get("dob", instance.dob)
        instance.email = validated_data.get("email", instance.email)
        instance.db_folder = validated_data.get("db_folder", instance.db_folder)
        instance.dropped_out = validated_data.get("dropped_out", instance.dropped_out)
        instance.college_id = validated_data.get("college_id", instance.college_id)

        mockdata = validated_data["mocktest"]
        print('md ', mockdata)
        if not hasattr(instance, "mocktest"):
            mocktestdata = {'problem1': 0, 'problem2': 0, 'problem3': 0, 'problem4': 0}
            mock = MockTest1.objects.create(Student=instance, **mocktestdata)
            setattr(instance, "mocktest", mock)

        instance.mocktest.problem1 = mockdata.get('problem1', instance.mocktest.problem1)
        instance.mocktest.problem2 = mockdata.get('problem2', instance.mocktest.problem2)
        instance.mocktest.problem3 = mockdata.get('problem3', instance.mocktest.problem3)
        instance.mocktest.problem4 = mockdata.get('problem4', instance.mocktest.problem4)
        instance.mocktest.totals = instance.mocktest.problem1 + instance.mocktest.problem2 + instance.mocktest.problem3 + instance.mocktest.problem4
        instance.mocktest.save()
        instance.save()
        return instance

