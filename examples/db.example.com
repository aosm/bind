
Title

Mac OS X Server 10.1: Configuring DNS in a NAT environment (db.example.com).

Summary

This article provides an example hostname-to-address lookup database file.  For more information on this article, please see article  ÒMac OS X Server 10.1: Configuring DNS in a NAT environment (Instructions).Ó


Discussion

[Disclaimer from Apple Legal]

------ Copy Below This Line --------
$TTL 86401
; db.example.com from Apple Knowledge Base Article Number
;
; CAUTION: Users should be aware that the incorrect configuration of DNS
; settings can result in serious system issues. It is recommended that only
; experienced users manipulate these settings.

;

example.com. IN SOA server.example.com. admin.server.example.com. (
                          10       ; Serial
                          10800    ; Refresh after 3 hours
                          3600     ; Retry after 1 hour
                          604800   ; Expire after 1 week
                          86400 )  ; Minimum TTL of 1 day

; Name servers

example.com.    IN NS  server.example.com.

; Primary Addresses

localhost.example.com.    IN A    127.0.0.1

server.example.com.    IN A    10.0.1.2
host3.example.com.    IN A    10.0.1.3
host4.example.com.    IN A    10.0.1.4
host5.example.com.    IN A    10.0.1.5
host6.example.com.    IN A    10.0.1.6
host7.example.com.    IN A    10.0.1.7
host8.example.com.    IN A    10.0.1.8
host9.example.com.    IN A    10.0.1.9
host10.example.com.    IN A    10.0.1.10
host11.example.com.    IN A    10.0.1.11
host12.example.com.    IN A    10.0.1.12
host13.example.com.    IN A    10.0.1.13
host14.example.com.    IN A    10.0.1.14
host15.example.com.    IN A    10.0.1.15
host16.example.com.    IN A    10.0.1.16
host17.example.com.    IN A    10.0.1.17
host18.example.com.    IN A    10.0.1.18
host19.example.com.    IN A    10.0.1.19
host20.example.com.    IN A    10.0.1.20
host21.example.com.    IN A    10.0.1.21
host22.example.com.    IN A    10.0.1.22
host23.example.com.    IN A    10.0.1.23
host24.example.com.    IN A    10.0.1.24
host25.example.com.    IN A    10.0.1.25
host26.example.com.    IN A    10.0.1.26
host27.example.com.    IN A    10.0.1.27
host28.example.com.    IN A    10.0.1.28
host29.example.com.    IN A    10.0.1.29
host30.example.com.    IN A    10.0.1.30
host31.example.com.    IN A    10.0.1.31
host32.example.com.    IN A    10.0.1.32
host33.example.com.    IN A    10.0.1.33
host34.example.com.    IN A    10.0.1.34
host35.example.com.    IN A    10.0.1.35
host36.example.com.    IN A    10.0.1.36
host37.example.com.    IN A    10.0.1.37
host38.example.com.    IN A    10.0.1.38
host39.example.com.    IN A    10.0.1.39
host40.example.com.    IN A    10.0.1.40
host41.example.com.    IN A    10.0.1.41
host42.example.com.    IN A    10.0.1.42
host43.example.com.    IN A    10.0.1.43
host44.example.com.    IN A    10.0.1.44
host45.example.com.    IN A    10.0.1.45
host46.example.com.    IN A    10.0.1.46
host47.example.com.    IN A    10.0.1.47
host48.example.com.    IN A    10.0.1.48
host49.example.com.    IN A    10.0.1.49
host50.example.com.    IN A    10.0.1.50
host51.example.com.    IN A    10.0.1.51
host52.example.com.    IN A    10.0.1.52
host53.example.com.    IN A    10.0.1.53
host54.example.com.    IN A    10.0.1.54
host55.example.com.    IN A    10.0.1.55
host56.example.com.    IN A    10.0.1.56
host57.example.com.    IN A    10.0.1.57
host58.example.com.    IN A    10.0.1.58
host59.example.com.    IN A    10.0.1.59
host60.example.com.    IN A    10.0.1.60
host61.example.com.    IN A    10.0.1.61
host62.example.com.    IN A    10.0.1.62
host63.example.com.    IN A    10.0.1.63
host64.example.com.    IN A    10.0.1.64
host65.example.com.    IN A    10.0.1.65
host66.example.com.    IN A    10.0.1.66
host67.example.com.    IN A    10.0.1.67
host68.example.com.    IN A    10.0.1.68
host69.example.com.    IN A    10.0.1.69
host70.example.com.    IN A    10.0.1.70
host71.example.com.    IN A    10.0.1.71
host72.example.com.    IN A    10.0.1.72
host73.example.com.    IN A    10.0.1.73
host74.example.com.    IN A    10.0.1.74
host75.example.com.    IN A    10.0.1.75
host76.example.com.    IN A    10.0.1.76
host77.example.com.    IN A    10.0.1.77
host78.example.com.    IN A    10.0.1.78
host79.example.com.    IN A    10.0.1.79
host80.example.com.    IN A    10.0.1.80
host81.example.com.    IN A    10.0.1.81
host82.example.com.    IN A    10.0.1.82
host83.example.com.    IN A    10.0.1.83
host84.example.com.    IN A    10.0.1.84
host85.example.com.    IN A    10.0.1.85
host86.example.com.    IN A    10.0.1.86
host87.example.com.    IN A    10.0.1.87
host88.example.com.    IN A    10.0.1.88
host89.example.com.    IN A    10.0.1.89
host90.example.com.    IN A    10.0.1.90
host91.example.com.    IN A    10.0.1.91
host92.example.com.    IN A    10.0.1.92
host93.example.com.    IN A    10.0.1.93
host94.example.com.    IN A    10.0.1.94
host95.example.com.    IN A    10.0.1.95
host96.example.com.    IN A    10.0.1.96
host97.example.com.    IN A    10.0.1.97
host98.example.com.    IN A    10.0.1.98
host99.example.com.    IN A    10.0.1.99
host100.example.com.    IN A    10.0.1.100
host101.example.com.    IN A    10.0.1.101
host102.example.com.    IN A    10.0.1.102
host103.example.com.    IN A    10.0.1.103
host104.example.com.    IN A    10.0.1.104
host105.example.com.    IN A    10.0.1.105
host106.example.com.    IN A    10.0.1.106
host107.example.com.    IN A    10.0.1.107
host108.example.com.    IN A    10.0.1.108
host109.example.com.    IN A    10.0.1.109
host110.example.com.    IN A    10.0.1.110
host111.example.com.    IN A    10.0.1.111
host112.example.com.    IN A    10.0.1.112
host113.example.com.    IN A    10.0.1.113
host114.example.com.    IN A    10.0.1.114
host115.example.com.    IN A    10.0.1.115
host116.example.com.    IN A    10.0.1.116
host117.example.com.    IN A    10.0.1.117
host118.example.com.    IN A    10.0.1.118
host119.example.com.    IN A    10.0.1.119
host120.example.com.    IN A    10.0.1.120
host121.example.com.    IN A    10.0.1.121
host122.example.com.    IN A    10.0.1.122
host123.example.com.    IN A    10.0.1.123
host124.example.com.    IN A    10.0.1.124
host125.example.com.    IN A    10.0.1.125
host126.example.com.    IN A    10.0.1.126
host127.example.com.    IN A    10.0.1.127
host128.example.com.    IN A    10.0.1.128
host129.example.com.    IN A    10.0.1.129
host130.example.com.    IN A    10.0.1.130
host131.example.com.    IN A    10.0.1.131
host132.example.com.    IN A    10.0.1.132
host133.example.com.    IN A    10.0.1.133
host134.example.com.    IN A    10.0.1.134
host135.example.com.    IN A    10.0.1.135
host136.example.com.    IN A    10.0.1.136
host137.example.com.    IN A    10.0.1.137
host138.example.com.    IN A    10.0.1.138
host139.example.com.    IN A    10.0.1.139
host140.example.com.    IN A    10.0.1.140
host141.example.com.    IN A    10.0.1.141
host142.example.com.    IN A    10.0.1.142
host143.example.com.    IN A    10.0.1.143
host144.example.com.    IN A    10.0.1.144
host145.example.com.    IN A    10.0.1.145
host146.example.com.    IN A    10.0.1.146
host147.example.com.    IN A    10.0.1.147
host148.example.com.    IN A    10.0.1.148
host149.example.com.    IN A    10.0.1.149
host150.example.com.    IN A    10.0.1.150
host151.example.com.    IN A    10.0.1.151
host152.example.com.    IN A    10.0.1.152
host153.example.com.    IN A    10.0.1.153
host154.example.com.    IN A    10.0.1.154
host155.example.com.    IN A    10.0.1.155
host156.example.com.    IN A    10.0.1.156
host157.example.com.    IN A    10.0.1.157
host158.example.com.    IN A    10.0.1.158
host159.example.com.    IN A    10.0.1.159
host160.example.com.    IN A    10.0.1.160
host161.example.com.    IN A    10.0.1.161
host162.example.com.    IN A    10.0.1.162
host163.example.com.    IN A    10.0.1.163
host164.example.com.    IN A    10.0.1.164
host165.example.com.    IN A    10.0.1.165
host166.example.com.    IN A    10.0.1.166
host167.example.com.    IN A    10.0.1.167
host168.example.com.    IN A    10.0.1.168
host169.example.com.    IN A    10.0.1.169
host170.example.com.    IN A    10.0.1.170
host171.example.com.    IN A    10.0.1.171
host172.example.com.    IN A    10.0.1.172
host173.example.com.    IN A    10.0.1.173
host174.example.com.    IN A    10.0.1.174
host175.example.com.    IN A    10.0.1.175
host176.example.com.    IN A    10.0.1.176
host177.example.com.    IN A    10.0.1.177
host178.example.com.    IN A    10.0.1.178
host179.example.com.    IN A    10.0.1.179
host180.example.com.    IN A    10.0.1.180
host181.example.com.    IN A    10.0.1.181
host182.example.com.    IN A    10.0.1.182
host183.example.com.    IN A    10.0.1.183
host184.example.com.    IN A    10.0.1.184
host185.example.com.    IN A    10.0.1.185
host186.example.com.    IN A    10.0.1.186
host187.example.com.    IN A    10.0.1.187
host188.example.com.    IN A    10.0.1.188
host189.example.com.    IN A    10.0.1.189
host190.example.com.    IN A    10.0.1.190
host191.example.com.    IN A    10.0.1.191
host192.example.com.    IN A    10.0.1.192
host193.example.com.    IN A    10.0.1.193
host194.example.com.    IN A    10.0.1.194
host195.example.com.    IN A    10.0.1.195
host196.example.com.    IN A    10.0.1.196
host197.example.com.    IN A    10.0.1.197
host198.example.com.    IN A    10.0.1.198
host199.example.com.    IN A    10.0.1.199
host200.example.com.    IN A    10.0.1.200
host201.example.com.    IN A    10.0.1.201
host202.example.com.    IN A    10.0.1.202
host203.example.com.    IN A    10.0.1.203
host204.example.com.    IN A    10.0.1.204
host205.example.com.    IN A    10.0.1.205
host206.example.com.    IN A    10.0.1.206
host207.example.com.    IN A    10.0.1.207
host208.example.com.    IN A    10.0.1.208
host209.example.com.    IN A    10.0.1.209
host210.example.com.    IN A    10.0.1.210
host211.example.com.    IN A    10.0.1.211
host212.example.com.    IN A    10.0.1.212
host213.example.com.    IN A    10.0.1.213
host214.example.com.    IN A    10.0.1.214
host215.example.com.    IN A    10.0.1.215
host216.example.com.    IN A    10.0.1.216
host217.example.com.    IN A    10.0.1.217
host218.example.com.    IN A    10.0.1.218
host219.example.com.    IN A    10.0.1.219
host220.example.com.    IN A    10.0.1.220
host221.example.com.    IN A    10.0.1.221
host222.example.com.    IN A    10.0.1.222
host223.example.com.    IN A    10.0.1.223
host224.example.com.    IN A    10.0.1.224
host225.example.com.    IN A    10.0.1.225
host226.example.com.    IN A    10.0.1.226
host227.example.com.    IN A    10.0.1.227
host228.example.com.    IN A    10.0.1.228
host229.example.com.    IN A    10.0.1.229
host230.example.com.    IN A    10.0.1.230
host231.example.com.    IN A    10.0.1.231
host232.example.com.    IN A    10.0.1.232
host233.example.com.    IN A    10.0.1.233
host234.example.com.    IN A    10.0.1.234
host235.example.com.    IN A    10.0.1.235
host236.example.com.    IN A    10.0.1.236
host237.example.com.    IN A    10.0.1.237
host238.example.com.    IN A    10.0.1.238
host239.example.com.    IN A    10.0.1.239
host240.example.com.    IN A    10.0.1.240
host241.example.com.    IN A    10.0.1.241
host242.example.com.    IN A    10.0.1.242
host243.example.com.    IN A    10.0.1.243
host244.example.com.    IN A    10.0.1.244
host245.example.com.    IN A    10.0.1.245
host246.example.com.    IN A    10.0.1.246
host247.example.com.    IN A    10.0.1.247
host248.example.com.    IN A    10.0.1.248
host249.example.com.    IN A    10.0.1.249
host250.example.com.    IN A    10.0.1.250
host251.example.com.    IN A    10.0.1.251
host252.example.com.    IN A    10.0.1.252
host253.example.com.    IN A    10.0.1.253
host254.example.com.    IN A    10.0.1.254
------ Copy Above This Line --------


Apple internal section

This information is provided for user information only.  

Only Apple Professional Services offers support for BIND.

I will expand this section with more information.

--- Document ends here.

The following sections are not part of the published document.

Security level
Choose one level: Public

Originator
Garrett Kline / Jeremiah Isaacs

Reference(s)
DNS and BIND by Paul Albitz & Cricket Liu, bind 8.2.3 man pages, other online resources listed in the article.

-- 
Garrett Kline.
Worldwide AppleCare Support Engineer
Apple Computer, Inc.
gkline@apple.com
(408) 974-0665


