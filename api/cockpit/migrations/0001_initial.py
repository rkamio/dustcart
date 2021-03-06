# Generated by Django 2.0.1 on 2020-02-20 21:19

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Dustcart',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=32)),
                ('ip_address', models.CharField(max_length=32)),
                ('status', models.CharField(max_length=32)),
                ('builded_at', models.DateTimeField(verbose_name='date real dustcar builded')),
                ('created_at', models.DateTimeField(verbose_name='date record inserted')),
                ('updated_at', models.DateTimeField(verbose_name='date record updated')),
            ],
        ),
    ]
