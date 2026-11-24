from setuptools import find_packages
from setuptools import setup

setup(
    name='navi_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('navi_interfaces', 'navi_interfaces.*')),
)
