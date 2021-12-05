TEMPLATE = subdirs

SUBDIRS += \
	UnitTests \
        Course \
	Student

Course.subdir = course/Course
Student.depends = Course
