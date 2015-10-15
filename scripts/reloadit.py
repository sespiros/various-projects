#!/usr/bin/python
import urllib.request
import json

def main():
    banner()
    print ('Give your telephone number: ')
    number = input()
    print ('Give your reloadit code: ')
    code = input()

    good = False
    while not good:
        object = urllib.request.urlopen('http://whatsup.ogilvy.dev.pathfinder.gr/api?method=runLottery&msisdn='+str(number)+'&code='+str(code))
        object = json.loads(object.read().decode())
        object = object['extra']['chooseyourself']

        print ('Available Presents: \033[92m')
        for i in range(len(object)):
            print (str(i) + ' : ' + object[i]['title'])

        print ('\033[0m \nChoose a present (0-2) or simply press enter to try reloading new presents: ')
        choice = input()
        if choice != '':
            good = True
    prizeId = object[int(choice)]['prizeid']
    response = urllib.request.urlopen('http://whatsup.ogilvy.phaistosnetworks.gr/api?method=secondProvisioning&msisdn='+number+'&code='+code+'&prizeid='+str(prizeId))
    response = json.loads(response.read().decode())
    if response['response'] == '0':
        print ('\033[91m'+'[*] Program failed!'+'\033[0m')
    else:
        print ('\033[92m'+'[*] Message sent!'+'\033[0m')

def banner():
    print ('\033[94m' + '\n\
#################################\n\
#   WhatsUp Reloadit client     #\n\
#   Summer 2012                 #\n\
#                               #\n\
#   sespiros@gmail.com          #\n\
#################################'+ '\033[0m')

if __name__ == '__main__':
    main()
