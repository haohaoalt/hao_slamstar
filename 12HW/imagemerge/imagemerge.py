from pickletools import uint8
from sys import flags
import cv2 as cv
import numpy as np
left = cv.imread("/home/slam007/hao_slamstar/12HW/imagemerge/left.jpg")
right = cv.imread("/home/slam007/hao_slamstar/12HW/imagemerge/right.jpg")

orb = cv.ORB_create()

keypoint_left = orb.detect(left)
keypoint_right = orb.detect(right)
keypoint_left, describetion_left = orb.compute(left, keypoint_left)
keypoint_right, describetion_right = orb.compute(right,keypoint_right)

show_keypoint_left = cv.drawKeypoints(left, keypoints=keypoint_left, outImage=None)
show_keypoint_right = cv.drawKeypoints(right, keypoints=keypoint_right,outImage=None)

cv.imshow("left",show_keypoint_left)

cv.imshow("right",show_keypoint_right)
# cv.waitKey(0)

matcher = cv.BFMatcher(cv.NORM_HAMMING)
match_result = matcher.match(describetion_left, describetion_right)

min_distance = match_result[0].distance
max_distance = match_result[0].distance
for i in match_result:
    if i.distance < min_distance:
        min_distance = i.distance
    if i.distance > max_distance:
        max_distance = i.distance
# print(min_distance, max_distance)
h, w, c = left.shape
print(w,h,c)
filter_result = []
for j in match_result:
    if j.distance >= max(min_distance*2, 10):
        if j.distance <= min(max_distance/3, 100):
            filter_result.append(j)

result_image = cv.drawMatches(left, keypoint_left, right, keypoint_right, filter_result, outImg=None)
cv.imshow("match result", result_image)
cv.waitKey(0)

print("size of match point pair:",len(filter_result))
if len(filter_result) > 3:
    keypoint_left = np.float32([keypoint_left[k.queryIdx].pt for k in filter_result]).reshape(-1,1,2)
    keypoint_right = np.float32([keypoint_right[k.trainIdx].pt for k in filter_result]).reshape(-1,1,2)
    # M,MASK = cv.findFundamentalMat(keypoint_left, keypoint_right, cv.FM_RANSAC, 5)
    matrix, mask = cv.findHomography(keypoint_right, keypoint_left,cv.RANSAC, 3.0)
    print("trans matrix: ",matrix)
    print("++++++++++++++++++++++++++++++")
    print("len of mask: ", len(mask))
    # print(mask)

    match_mask = mask.ravel().tolist()
    points = np.float32([[0,0],[0,h-1],[w-1,h-1],[w-1,0]]).reshape(-1,1,2)
    dest_point = cv.perspectiveTransform(points, matrix)
    print("dest points: ",dest_point)
    final_image = np.zeros([h,2*w,3],dtype = "uint8")
    warp_image = cv.warpPerspective(right, matrix, (2*w, h), flags=cv.INTER_LINEAR)
    cv.imshow("warp image",warp_image)
    final_image[0:h,0:w] = left
    for i in range(h):
        for j in range(2*w):
            if (warp_image[i][j].any() != 0):
                final_image[i][j] = warp_image[i][j]
    
    cv.imshow("final image",final_image)
    cv.waitKey(0)